CREATE TABLE branch(
    branch_name VARCHAR(250),
    branch_city VARCHAR(250), 
    assets NUMBER(10),
    PRIMARY KEY (branch_name)
);

INSERT into branch VALUES ('Agrani', 'Uttara', 1000000);
INSERT into branch VALUES ('Sonali', 'Mirpur', 1500000);
INSERT into branch VALUES ('Rupali', 'Motijheel', 900000);