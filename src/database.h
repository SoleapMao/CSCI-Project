#pragma once
#include <sqlite3.h>
#include <stdexcept>
#include <string>
#include <vector>

struct Transaction
{
    int id;
    std::string type; // "income" or "expense"
    double amount;
    std::string note;
    std::string createdAt;
};

class Database
{
public:
    // Opens (or creates) the database file and makes sure the table exists.
    explicit Database(const std::string &path)
    {
        if (sqlite3_open(path.c_str(), &db_) != SQLITE_OK)
            throw std::runtime_error(sqlite3_errmsg(db_));
        run("CREATE TABLE IF NOT EXISTS transactions ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "type TEXT NOT NULL CHECK (type IN ('income','expense')),"
            "amount REAL NOT NULL CHECK (amount > 0),"
            "note TEXT,"
            "created_at TEXT NOT NULL DEFAULT (datetime('now')))");
    }
    ~Database() { sqlite3_close(db_); }
    Database(const Database &) = delete;
    Database &operator=(const Database &) = delete;

    // Save one income or expense.
    void add(const std::string &type, double amount, const std::string &note = "")
    {
        sqlite3_stmt *st = prepare("INSERT INTO transactions (type, amount, note) VALUES (?, ?, ?)");
        sqlite3_bind_text(st, 1, type.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_double(st, 2, amount);
        sqlite3_bind_text(st, 3, note.c_str(), -1, SQLITE_TRANSIENT);
        int rc = sqlite3_step(st);
        sqlite3_finalize(st);
        if (rc != SQLITE_DONE)
            throw std::runtime_error(sqlite3_errmsg(db_));
    }

    // Sum of all rows of one type.
    double total(const std::string &type)
    {
        sqlite3_stmt *st = prepare("SELECT COALESCE(SUM(amount), 0) FROM transactions WHERE type = ?");
        sqlite3_bind_text(st, 1, type.c_str(), -1, SQLITE_TRANSIENT);
        double sum = 0;
        if (sqlite3_step(st) == SQLITE_ROW)
            sum = sqlite3_column_double(st, 0);
        sqlite3_finalize(st);
        return sum;
    }

    double balance() { return total("income") - total("expense"); }

    // All rows of one type, oldest first.
    std::vector<Transaction> list(const std::string &type)
    {
        sqlite3_stmt *st = prepare("SELECT id, type, amount, note, created_at "
                                   "FROM transactions WHERE type = ? ORDER BY id");
        sqlite3_bind_text(st, 1, type.c_str(), -1, SQLITE_TRANSIENT);
        std::vector<Transaction> rows;
        while (sqlite3_step(st) == SQLITE_ROW)
        {
            Transaction t;
            t.id = sqlite3_column_int(st, 0);
            t.type = text(st, 1);
            t.amount = sqlite3_column_double(st, 2);
            t.note = text(st, 3);
            t.createdAt = text(st, 4);
            rows.push_back(t);
        }
        sqlite3_finalize(st);
        return rows;
    }

private:
    sqlite3 *db_ = nullptr;

    void run(const char *sql)
    {
        char *err = nullptr;
        if (sqlite3_exec(db_, sql, nullptr, nullptr, &err) != SQLITE_OK)
        {
            std::string msg = err ? err : "SQL error";
            sqlite3_free(err);
            throw std::runtime_error(msg);
        }
    }

    sqlite3_stmt *prepare(const char *sql)
    {
        sqlite3_stmt *st = nullptr;
        if (sqlite3_prepare_v2(db_, sql, -1, &st, nullptr) != SQLITE_OK)
            throw std::runtime_error(sqlite3_errmsg(db_));
        return st;
    }

    static std::string text(sqlite3_stmt *st, int col)
    {
        const unsigned char *p = sqlite3_column_text(st, col);
        return p ? reinterpret_cast<const char *>(p) : "";
    }
};
