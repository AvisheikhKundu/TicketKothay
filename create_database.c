void createTable(sqlite3 *db) {
    const char *sql = "CREATE TABLE IF NOT EXISTS Reservations ("
                      "PassnNo INTEGER PRIMARY KEY, "
                      "Name TEXT NOT NULL);";
    char *errMsg;
    int exit = sqlite3_exec(db, sql, NULL, 0, &errMsg);
    if (exit != SQLITE_OK) {
        fprintf(stderr, "Error creating table: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
}