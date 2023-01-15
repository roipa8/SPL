import sqlite3
import atexit
from DaoDto import _Vaccines, _Suppliers, _Clinics, _Logistics, Vaccine, Supplier, Clinic, Logistic


class _Repository:
    def __init__(self):
        self._conn = sqlite3.connect('database.db')
        self.vaccines = _Vaccines(self._conn)
        self.suppliers = _Suppliers(self._conn)
        self.clinics = _Clinics(self._conn)
        self.logistics = _Logistics(self._conn)

    def _close(self):
        self._conn.commit()
        self._conn.close()

    def create_tables(self):
        self._conn.executescript("""
        CREATE TABLE IF NOT EXISTS `vaccines` (
	`id`	INTEGER,
	`date`	DATE NOT NULL,
	`supplier`	INTEGER,
	`quantity`	INTEGER NOT NULL,
	PRIMARY KEY(`id`),
	FOREIGN KEY(`supplier`) REFERENCES `suppliers`(`id`)
);
CREATE TABLE IF NOT EXISTS `suppliers` (
	`id`	INTEGER,
	`name`	TEXT NOT NULL,
	`logistic`	INTEGER,
	PRIMARY KEY(`id`),
	FOREIGN KEY(`logistic`) REFERENCES `logistics`(`id`)
);
CREATE TABLE IF NOT EXISTS `logistics` (
	`id`	INTEGER,
	`name`	TEXT NOT NULL,
	`count_sent`	INTEGER NOT NULL,
	`count_received`	INTEGER NOT NULL,
	PRIMARY KEY(`id`)
);
CREATE TABLE IF NOT EXISTS `clinics` (
	`id`	INTEGER,
	`location`	TEXT NOT NULL,
	`demand`	INTEGER NOT NULL,
	`logistic`	INTEGER,
	FOREIGN KEY(`logistic`) REFERENCES `logistics`(`id`),
	PRIMARY KEY(`id`)
);
""")

    def sum(self):
        c = self._conn.cursor()
        c.execute("""SELECT SUM(quantity),
        (SELECT SUM(demand) FROM clinics), 
        (SELECT SUM(count_received) FROM logistics), 
        (SELECT SUM(count_sent) FROM logistics) FROM vaccines
        """)
        return str(c.fetchone())


r = _Repository()
atexit.register(r._close)

