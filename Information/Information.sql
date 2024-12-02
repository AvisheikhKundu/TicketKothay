sqlite3 *db;
char *err_msg = 0;
int rc = sqlite3_open("bus_reservations.db", &db);

if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return 1;
}