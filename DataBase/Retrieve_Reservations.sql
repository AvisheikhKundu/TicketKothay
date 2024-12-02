const char *sql_select = "SELECT * FROM Reservations WHERE ReservationNumber = ?;";
rc = sqlite3_prepare_v2(db, sql_select, -1, &stmt, 0);

if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return 1;
}

sqlite3_bind_int(stmt, 1, reservationNo);

while (sqlite3_step(stmt) == SQLITE_ROW) {
    int id = sqlite3_column_int(stmt, 0);
    int customerID = sqlite3_column_int(stmt, 1);
    int busNumber = sqlite3_column_int(stmt, 2);
    int seatNumber = sqlite3_column_int(stmt, 3);
    int reservationNumber = sqlite3_column_int(stmt, 4);

    printf("ID: %d, CustomerID: %d, BusNumber: %d, SeatNumber: %d, ReservationNumber: %d\n", id, customerID, busNumber, seatNumber, reservationNumber);
}

sqlite3_finalize(stmt);