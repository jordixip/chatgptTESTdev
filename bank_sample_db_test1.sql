-- Create the customers table
CREATE TABLE customers (
    id INT PRIMARY KEY,
    first_name VARCHAR(255),
    last_name VARCHAR(255),
    email VARCHAR(255) UNIQUE,
    phone VARCHAR(255),
    address VARCHAR(255)
);

-- Create the savings accounts table
CREATE TABLE savings_accounts (
    account_number INT PRIMARY KEY,
    customer_id INT,
    balance DECIMAL(10, 2),
    FOREIGN KEY (customer_id) REFERENCES customers(id)
);

-- Create the credit cards table
CREATE TABLE credit_cards (
    card_number VARCHAR(16) PRIMARY KEY,
    customer_id INT,
    credit_limit DECIMAL(10, 2),
    FOREIGN KEY (customer_id) REFERENCES customers(id)
);

-- Create the loans table
CREATE TABLE loans (
    loan_number INT PRIMARY KEY,
    customer_id INT,
    amount DECIMAL(10, 2),
    interest_rate DECIMAL(5, 2),
    FOREIGN KEY (customer_id) REFERENCES customers(id)
);

-- Create the transaction table
CREATE TABLE transactions (
    id INT PRIMARY KEY,
    account_number INT,
    transaction_date DATE,
    transaction_amount DECIMAL(10, 2),
    transaction_type ENUM('debit', 'credit'),
    FOREIGN KEY (account_number) REFERENCES savings_accounts(account_number)
);
