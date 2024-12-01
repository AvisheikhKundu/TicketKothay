CREATE TABLE IF NOT EXISTS Reservations (
    PassnNo INTEGER PRIMARY KEY,
    Name TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS Reservations (
    PassnNo INTEGER PRIMARY KEY,
    Name TEXT NOT NULL,
    ReservationDate DATE NOT NULL,
    NumberOfGuests INTEGER NOT NULL,
    ContactNumber TEXT
);

CREATE TABLE IF NOT EXISTS Reservations (
    PassnNo INTEGER PRIMARY KEY,
    Name TEXT NOT NULL,
    ReservationDate DATE NOT NULL,
    NumberOfGuests INTEGER NOT NULL,
    ContactNumber TEXT
);