-- Part 3: Database Query Handling
-- Tables
-- Customers (customer_id, name, email)
-- Books (book_id, title, author, price)
-- Orders (order_id, customer_id, order_date)
-- OrderDetails (order_id, book_id, quantity)
-- 1. Retrieve the top 5 customers who have purchased the most books by quantity over the last year.
SELECT c.customer_id,
    c.name,
    SUM(od.quantity) AS total_books
FROM Customers c
    JOIN Orders o ON c.customer_id = o.customer_id
    JOIN OrderDetails od ON o.order_id = od.order_id
WHERE o.order_date >= DATEADD(YEAR, -1, GETDATE())
GROUP BY c.customer_id,
    c.name
ORDER BY total_books DESC
LIMIT 5;



-- 2. Calculate the total revenue generated from book sales by each author.

SELECT b.author,
    SUM(od.quantity * b.price) AS total_revenue
FROM Books b
    JOIN OrderDetails od ON b.book_id = od.book_id
GROUP BY b.author
ORDER BY total_revenue DESC;


-- 3. Retrieve all books that have been ordered more than 10 times along with the total quantity ordered for each book.
SELECT b.book_id,
    b.title,
    SUM(od.quantity) AS total_quantity
FROM Books b
    JOIN OrderDetails od ON b.book_id = od.book_id
GROUP BY b.book_id,
    b.title
HAVING total_quantity > 10;
