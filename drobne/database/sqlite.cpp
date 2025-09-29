#include <database/sqlite.hpp>
#include <sqlite3.h>
#include <filesystem>
#include <string>
#include <iostream>

namespace database {
    SQLite::~SQLite() {
        sqlite3_close(m_db);
    }

    int SQLite::create(const std::string name) {
        std::filesystem::create_directory(databaseFolder);

        int status;
        if (name == "") {   
            status = open(databaseFolder + "/" + DEFAULT_NAME);
        }
        else {
            status = open(databaseFolder + "/" + name + ".db");
        }

        if (status != SQLITE_OK) {
            std::cerr << "Can't open database: \n" << sqlite3_errmsg (m_db);
            return status;
        }

        // 1.1. Lookup: Entity Types
        const std::string createEntityTypesSQL = R"===(
        CREATE TABLE IF NOT EXISTS EntityTypes (
            entity_type_id INTEGER PRIMARY KEY,
            type_name VARCHAR(20) NOT NULL UNIQUE
        );
        )===";

        // 1.2. Lookup: Account Types
        const std::string createAccountTypesSQL = R"(
        CREATE TABLE IF NOT EXISTS AccountTypes (
            account_type_id INTEGER PRIMARY KEY,
            type_name VARCHAR(50) NOT NULL UNIQUE
        );
        )";

        // 1.3. Lookup: SubAccount Types
        const std::string createSubAccountTypesSQL = R"===(
        CREATE TABLE IF NOT EXISTS SubAccountTypes (
            sub_account_type_id INTEGER PRIMARY KEY,
            type_name VARCHAR(50) NOT NULL UNIQUE
        );
        )===";

        // 1.4. Lookup: Category Types
        const std::string createCategoryTypesSQL = R"===(
        CREATE TABLE IF NOT EXISTS CategoryTypes (
            category_type_id INTEGER PRIMARY KEY,
            type_name VARCHAR(50) NOT NULL UNIQUE
        );
        )===";

        // 1.5. Lookup: Transaction Types (Debit/Credit/Fee)
        const std::string createTransactionTypesSQL = R"===(
        CREATE TABLE IF NOT EXISTS TransactionTypes (
            transaction_type_id INTEGER PRIMARY KEY,
            type_name VARCHAR(20) NOT NULL UNIQUE
        );
        )===";

        // 1.6. Lookup: Transaction Statuses (Pending/Cleared/Reconciled)
        const std::string createTransactionStatusesSQL = R"===(
        CREATE TABLE IF NOT EXISTS TransactionStatuses (
            status_id INTEGER PRIMARY KEY,
            status_name VARCHAR(20) NOT NULL UNIQUE
        );
        )===";

        // 1.7. Lookup: Investment Asset Types
        const std::string createInvestmentAssetTypesSQL = R"===(
        CREATE TABLE IF NOT EXISTS InvestmentAssetTypes (
            asset_type_id INTEGER PRIMARY KEY,
            type_name VARCHAR(50) NOT NULL UNIQUE
        );
        )===";

        // 1.8. Lookup: Investment Transaction Types (Buy/Sell/Dividend)
        const std::string createInvestmentTransactionTypesSQL = R"===(
        CREATE TABLE IF NOT EXISTS InvestmentTransactionTypes (
            inv_transaction_type_id INTEGER PRIMARY KEY,
            type_name VARCHAR(50) NOT NULL UNIQUE
        );
        )===";

        for (const std::string &val : {createEntityTypesSQL, createAccountTypesSQL, createSubAccountTypesSQL, createCategoryTypesSQL, createTransactionTypesSQL, createTransactionStatusesSQL, createInvestmentAssetTypesSQL, createInvestmentTransactionTypesSQL}) {
            status = sqlite3_exec(m_db, val.c_str(), nullptr, nullptr, nullptr);
            if (status != SQLITE_OK) {
                std::cerr << "Can't exec: \n" << val << "\n" << sqlite3_errmsg (m_db);
                return status;
            }
        }

        // 2. Users
        const std::string createUsersSQL = R"===(
        CREATE TABLE IF NOT EXISTS Users (
            user_id          INTEGER PRIMARY KEY,
            username         VARCHAR(50) NOT NULL UNIQUE,
            email            VARCHAR(100) NOT NULL UNIQUE,
            created_at       INTEGER DEFAULT (unixepoch())
        );
        )===";

        // 3. FinancialEntities
        const std::string createFinancialEntitiesSQL = R"===(
        CREATE TABLE IF NOT EXISTS FinancialEntities (
            entity_id        INTEGER PRIMARY KEY,
            user_id          INTEGER NOT NULL,
            entity_type_id   INTEGER NOT NULL,
            entity_name      VARCHAR(100) NOT NULL,
            institution_name VARCHAR(100),
            is_active        BOOLEAN DEFAULT 1,
            FOREIGN KEY (user_id) REFERENCES Users(user_id),
            FOREIGN KEY (entity_type_id) REFERENCES EntityTypes(entity_type_id)
        );
        )===";

        // 4. Accounts
        const std::string createAccountsSQL = R"===(
        CREATE TABLE IF NOT EXISTS Accounts (
            account_id           INTEGER PRIMARY KEY,
            entity_id            INTEGER NOT NULL,
            account_type_id      INTEGER NOT NULL,
            account_name         VARCHAR(100) NOT NULL,
            currency             CHAR(3) NOT NULL,
            initial_balance      DECIMAL(15, 2) DEFAULT 0.00,
            last_sync_balance    DECIMAL(15, 2),
            last_sync_at         INTEGER DEFAULT (unixepoch()),
            FOREIGN KEY (entity_id) REFERENCES FinancialEntities(entity_id),
            FOREIGN KEY (account_type_id) REFERENCES AccountTypes(account_type_id)
        );
        )===";

        // 5. SubAccounts (Goals/Categories)
        const std::string createSubAccountsSQL = R"===(
        CREATE TABLE IF NOT EXISTS SubAccounts (
            sub_account_id       INTEGER PRIMARY KEY,
            user_id              INTEGER NOT NULL,
            sub_account_type_id  INTEGER NOT NULL,
            sub_account_name     VARCHAR(100) NOT NULL,
            goal_amount          DECIMAL(15, 2),
            goal_due_date        INTEGER DEFAULT NULL,
            FOREIGN KEY (user_id) REFERENCES Users(user_id),
            FOREIGN KEY (sub_account_type_id) REFERENCES SubAccountTypes(sub_account_type_id)
        );
        )===";

        // 6. SubAccountLinkage (Many-to-Many allocation)
        const std::string createSubAccountLinkageSQL = R"===(
        CREATE TABLE IF NOT EXISTS SubAccountLinkage (
            linkage_id           INTEGER PRIMARY KEY,
            sub_account_id       INTEGER NOT NULL,
            account_id           INTEGER NOT NULL,
            allocated_amount     DECIMAL(15, 2) DEFAULT 0.00,
            priority             INTEGER,
            UNIQUE (sub_account_id, account_id),
            FOREIGN KEY (sub_account_id) REFERENCES SubAccounts(sub_account_id),
            FOREIGN KEY (account_id) REFERENCES Accounts(account_id)
        );
        )===";

        // 7. Categories
        const std::string createCategoriesSQL = R"===(
        CREATE TABLE IF NOT EXISTS Categories (
            category_id          INTEGER PRIMARY KEY,
            user_id              INTEGER,
            category_type_id     INTEGER NOT NULL,
            category_name        VARCHAR(50) NOT NULL,
            parent_category_id   INTEGER, -- Self-referencing FK
            FOREIGN KEY (user_id) REFERENCES Users(user_id),
            FOREIGN KEY (category_type_id) REFERENCES CategoryTypes(category_type_id),
            FOREIGN KEY (parent_category_id) REFERENCES Categories(category_id)
        );
        )===";

        // 8. Transactions (The core ledger)
        const std::string createTransactionsSQL = R"===(
        CREATE TABLE IF NOT EXISTS Transactions (
            transaction_id       INTEGER PRIMARY KEY,
            account_id           INTEGER NOT NULL,
            sub_account_id       INTEGER,
            category_id          INTEGER NOT NULL,
            transaction_type_id  INTEGER NOT NULL,
            status_id            INTEGER NOT NULL,
            transaction_date     INTEGER NOT NULL,
            amount               DECIMAL(15, 2) NOT NULL, -- Negative for debits/expenses
            description          TEXT,
            payee                VARCHAR(100),
            created_at           INTEGER DEFAULT (unixepoch()),
            FOREIGN KEY (account_id) REFERENCES Accounts(account_id),
            FOREIGN KEY (sub_account_id) REFERENCES SubAccounts(sub_account_id),
            FOREIGN KEY (category_id) REFERENCES Categories(category_id),
            FOREIGN KEY (transaction_type_id) REFERENCES TransactionTypes(transaction_type_id),
            FOREIGN KEY (status_id) REFERENCES TransactionStatuses(status_id)
        );
        )===";

        // 9. Transfers (Links two Transactions entries)
        const std::string createTransfersSQL = R"===(
        CREATE TABLE IF NOT EXISTS Transfers (
            transfer_id              INTEGER PRIMARY KEY,
            source_transaction_id    INTEGER NOT NULL,
            destination_account_id   INTEGER NOT NULL,
            destination_transaction_id INTEGER NOT NULL,
            transfer_date            INTEGER NOT NULL,
            amount                   DECIMAL(15, 2) NOT NULL,
            memo                     TEXT,
            FOREIGN KEY (source_transaction_id) REFERENCES Transactions(transaction_id),
            FOREIGN KEY (destination_account_id) REFERENCES Accounts(account_id),
            FOREIGN KEY (destination_transaction_id) REFERENCES Transactions(transaction_id)
        );
        )===";

        // 10. Investments (Asset definition)
        const std::string createInvestmentsSQL = R"===(
        CREATE TABLE IF NOT EXISTS Investments (
            investment_id        INTEGER PRIMARY KEY,
            asset_type_id        INTEGER NOT NULL,
            ticker               VARCHAR(10) NOT NULL UNIQUE,
            asset_name           VARCHAR(100) NOT NULL,
            is_tracked           BOOLEAN DEFAULT 1,
            FOREIGN KEY (asset_type_id) REFERENCES InvestmentAssetTypes(asset_type_id)
        );
        )===";

        // 11. InvestmentTransactions (Specific trading actions)
        const std::string createInvestmentTransactionsSQL = R"===(
        CREATE TABLE IF NOT EXISTS InvestmentTransactions (
            inv_transaction_id      INTEGER PRIMARY KEY,
            account_id              INTEGER NOT NULL,
            investment_id           INTEGER NOT NULL,
            inv_transaction_type_id INTEGER NOT NULL,
            transaction_date        INTEGER NOT NULL,
            shares_quantity         DECIMAL(15, 8) NOT NULL,
            price_per_share         DECIMAL(15, 4) NOT NULL,
            total_amount            DECIMAL(15, 2) NOT NULL,
            commission              DECIMAL(15, 2) DEFAULT 0.00,
            FOREIGN KEY (account_id) REFERENCES Accounts(account_id),
            FOREIGN KEY (investment_id) REFERENCES Investments(investment_id),
            FOREIGN KEY (inv_transaction_type_id) REFERENCES InvestmentTransactionTypes(inv_transaction_type_id)
        );
        )===";

        for (const std::string &val : {createUsersSQL, createFinancialEntitiesSQL, createAccountsSQL, createSubAccountsSQL, createSubAccountLinkageSQL, createCategoriesSQL, createTransactionsSQL, createTransfersSQL, createInvestmentsSQL, createInvestmentTransactionsSQL}) {
            status = sqlite3_exec(m_db, val.c_str(), nullptr, nullptr, nullptr);
            if (status != SQLITE_OK) {
                std::cerr << "Can't exec: \n"  << val << "\n" << sqlite3_errmsg (m_db);
                return status;
            }
        }

        return status;
    }

    int SQLite::open(const std::string path) {
        int status = sqlite3_open(path.c_str(), &m_db);

        if (status != SQLITE_OK) {
            // ERROR SQLITE
            std::cerr << "Can't open database: \n" << sqlite3_errmsg (m_db);
        }

        return status;
    }

    int SQLite::prepare(const std::string statement, const unsigned int flags, sqlite3_stmt** handle) {
        int status = sqlite3_prepare_v3(m_db, statement.c_str(), statement.length(), flags, handle, nullptr);
        
        if (status != SQLITE_OK) {
            // Error statement
            std::cerr << "Can't prepare statement: \n" << sqlite3_errmsg (m_db);
        }

        return status;
    }

    int SQLite::bind(sqlite3_stmt* sqlite_statement, int index, int value) {
        int status = sqlite3_bind_int(sqlite_statement, index, value);

        if (status != SQLITE_OK) {
            // Error statement
            std::cerr << "Can't bind value: \n" << sqlite3_errmsg (m_db);
            sqlite3_finalize(sqlite_statement);
        }

        return status;
    }

    int SQLite::bind(sqlite3_stmt* sqlite_statement, int index, sqlite3_int64 value) {
        int status = sqlite3_bind_int64(sqlite_statement, index, value);

        if (status != SQLITE_OK) {
            // Error statement
            std::cerr << "Can't bind value: \n" << sqlite3_errmsg (m_db);
            sqlite3_finalize(sqlite_statement);
        }

        return status;
    }

    int SQLite::bind(sqlite3_stmt* sqlite_statement, int index, double value) {
        int status = sqlite3_bind_double(sqlite_statement, index, value);

        if (status != SQLITE_OK) {
            // Error statement
            std::cerr << "Can't bind value: \n" << sqlite3_errmsg (m_db);
            sqlite3_finalize(sqlite_statement);
        }

        return status;
    }

    int SQLite::bind(sqlite3_stmt* sqlite_statement, int index, std::string value, sqlite3_destructor_type destructor) {
        int status = sqlite3_bind_text(sqlite_statement, index, value.c_str(), value.size(), destructor);

        if (status != SQLITE_OK) {
            // Error statement
            std::cerr << "Can't bind value: \n" << sqlite3_errmsg (m_db);
            sqlite3_finalize(sqlite_statement);
        }

        return status;
    }

    int SQLite::bind(sqlite3_stmt* sqlite_statement, int index, const void* value, int size, sqlite3_destructor_type destructor) {
        int status = sqlite3_bind_blob(sqlite_statement, index, value, size, destructor);

        if (status != SQLITE_OK) {
            // Error statement
            std::cerr << "Can't bind value: \n" << sqlite3_errmsg (m_db);
            sqlite3_finalize(sqlite_statement);
        }

        return status;
    }

    int SQLite::step(sqlite3_stmt* sqlite_statement) {
        int status = sqlite3_step(sqlite_statement);

        switch (status) {
            case SQLITE_OK:
            case SQLITE_ROW:
            case SQLITE_DONE:
                break;
            default:
                std::cerr << "Can't execute statement: \n" << sqlite3_errmsg (m_db);
                sqlite3_finalize(sqlite_statement);
                break;
        }

        return status;
    }
}