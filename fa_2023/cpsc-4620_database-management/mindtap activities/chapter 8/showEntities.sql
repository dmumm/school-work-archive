SHOW TABLES FROM InstantRide;

-- List all user-defined views excluding system views
SELECT TABLE_NAME
FROM information_schema.VIEWS
WHERE TABLE_SCHEMA NOT IN ('mysql', 'information_schema', 'performance_schema', 'sys');

SELECT "-----";

-- List all non-system routines (procedures and functions)
SELECT ROUTINE_NAME, ROUTINE_TYPE
FROM information_schema.routines
WHERE ROUTINE_SCHEMA NOT IN ('mysql', 'information_schema', 'performance_schema', 'sys');
