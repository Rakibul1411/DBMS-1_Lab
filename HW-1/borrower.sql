CREATE TABLE borrower(
    customer_name VARCHAR(250),
    loan_number VARCHAR(250),
    CONSTRAINT pk_borrower PRIMARY KEY (customer_name, loan_number),
    CONSTRAINT fk_customer_borrower FOREIGN KEY (customer_name) REFERENCES customer(customer_name),
    CONSTRAINT fk_loan FOREIGN KEY (loan_number) REFERENCES loan(loan_number)
);

INSERT into borrower VALUES ('Zisun', 'L-1003');
INSERT into borrower VALUES ('Shakib', 'L-1001');
INSERT into borrower VALUES ('Kibria', 'L-1002');