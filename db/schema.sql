-- Student Money Tracker: database schema (SQLite)
-- One table. Each row is one income or expense.

CREATE TABLE IF NOT EXISTS transactions (
    id         INTEGER PRIMARY KEY AUTOINCREMENT,
    type       TEXT NOT NULL CHECK (type IN ('income', 'expense')),
    amount     REAL NOT NULL CHECK (amount > 0),
    note       TEXT,
    created_at TEXT NOT NULL DEFAULT (datetime('now'))
);

-- Handy queries to try in the sqlite3 shell:

-- Current balance
-- SELECT COALESCE(SUM(CASE WHEN type = 'income' THEN amount ELSE -amount END), 0) AS balance
-- FROM transactions;

-- Income and expenses per month (this is what the chart shows)
-- SELECT strftime('%Y-%m', created_at) AS month,
--        SUM(CASE WHEN type = 'income'  THEN amount ELSE 0 END) AS income,
--        SUM(CASE WHEN type = 'expense' THEN amount ELSE 0 END) AS expenses
-- FROM transactions
-- GROUP BY month
-- ORDER BY month;
