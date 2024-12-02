const char *sql_create_table = "CREATE TABLE IF NOT EXISTS Reservations("
                               "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                               "CustomerID INT, "
                               "BusNumber INT, "
                               "SeatNumber INT, "
                               "ReservationNumber INT);";

rc = sqlite3_exec(db, sql_create_table, 0, 0, &err_msg);

if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
    sqlite3_close(db);
    return 1;
}