const char *sql_insert = "INSERT INTO Reservations (CustomerID, BusNumber, SeatNumber, ReservationNumber) VALUES (?, ?, ?, ?);";
sqlite3_stmt *stmt;

rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, 0);

if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return 1;
}

sqlite3_bind_int(stmt, 1, custID);
sqlite3_bind_int(stmt, 2, choice);
sqlite3_bind_int(stmt, 3, seatNumber);
sqlite3_bind_int(stmt, 4, randomNum);

rc = sqlite3_step(stmt);

if (rc != SQLITE_DONE) {
    fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
}

sqlite3_finalize(stmt);