class Vaccine:
    def __init__(self, id, date, supplier, quantity):
        self.id = id
        self.date = date
        self.quantity = quantity
        self.supplier = supplier


class Supplier:
    def __init__(self, id, name, logistic):
        self.id = id
        self.name = name
        self.logistic = logistic


class Clinic:
    def __init__(self, id, location, demand, logistic):
        self.id = id
        self.location = location
        self.demand = demand
        self.logistic = logistic


class Logistic:
    def __init__(self, id, name, count_sent, count_received):
        self.id = id
        self.name = name
        self.count_sent = count_sent
        self.count_received = count_received


class _Vaccines:
    def __init__(self, conn):
        self._conn = conn

    def insert(self, Vaccine):
        self._conn.execute("""
               INSERT INTO vaccines (id, date, Supplier, quantity) VALUES (?, ?, ?, ?)
           """, [Vaccine.id ,Vaccine.date, Vaccine.supplier, Vaccine.quantity])

    def orderByDate(self):
        self._conn.execute("""
        SELECT * FROM vaccines ORDER BY date
        """)

    def delete(self):
        self._conn.execute("""
        DELETE FROM vaccines WHERE quantity = 0
        """)

    def reduceAmount(self,amount,id):
        self._conn.execute("""
        UPDATE vaccines SET quantity = quantity - ? WHERE id = ?
        """, [amount,id])

    def findOldest(self):
        c = self._conn.cursor()
        c.execute("""
        SELECT * FROM vaccines LIMIT 1
        """)
        return Vaccine(*c.fetchone())

    def reduceToZero(self,id):
        self._conn.execute("""
        UPDATE vaccines SET quantity = 0 WHERE id = ?
        """, [id])

    def sumInv(self):
        c = self._conn.cursor()
        c.execute("""
        SELECT SUM(quantity) FROM vaccines
        """)
        return str(c.fetchone())

class _Suppliers:
    def __init__(self, conn):
        self._conn = conn

    def insert(self, Supplier):
        self._conn.execute("""
               INSERT INTO suppliers (id, 'name', Logistic) VALUES (?, ?, ?)
           """, [Supplier.id ,Supplier.name, Supplier.logistic])

    def find(self, name):
        c = self._conn.cursor()
        c.execute("""
        SELECT * FROM suppliers WHERE name = ?
        """, [name])
        return Supplier(*c.fetchone())

    def findLogOfSup(self, name):
        c = self._conn.cursor()
        c.execute(""" 
        SELECT * FROM suppliers WHERE name = ? 
         """, [name])
        return Supplier(*c.fetchone())


class _Clinics:
    def __init__(self, conn):
        self._conn = conn

    def insert(self, Clinic):
        self._conn.execute("""
               INSERT INTO clinics (id, location, demand, Logistic) VALUES (?, ?, ?, ?)
           """, [Clinic.id ,Clinic.location, Clinic.demand, Clinic.logistic])

    def find(self, clinic):
        c = self._conn.cursor()
        c.execute("""
        SELECT * FROM clinics WHERE location = ? 
        """, [clinic])
        return Clinic(*c.fetchone())

    def update(self,name, amount):
        self._conn.execute("""
        UPDATE clinics SET demand = demand - ? WHERE location = ?
        """, [amount, name])

    def sumDem(self):
        c = self._conn.cursor()
        c.execute("""
        SELECT SUM(demand) FROM clinics
        """)
        return str(c.fetchone())

class _Logistics:
    def __init__(self, conn):
        self._conn = conn

    def insert(self, Logistic):
        self._conn.execute("""
               INSERT INTO logistics (id,'name', count_sent, count_received) VALUES (?, ?, ?, ?)
           """, [Logistic.id ,Logistic.name, Logistic.count_sent, Logistic.count_received])

    def find(self, id):
        c = self._conn.cursor()
        c.execute(""" 
        SELECT * FROM logistics where id = ? 
         """, [id])
        return Logistic(*c.fetchone())

    def updateRec(self, id, amount):
        self._conn.execute(""" 
        UPDATE logistics SET count_received = count_received + ? WHERE id = ? 
         """, [amount, id])

    def updateSent(self, id, amount):
        self._conn.execute(""" 
        UPDATE logistics SET count_sent = count_sent + ? WHERE id = ? 
         """, [amount, id])

    def sumRec(self):
        c = self._conn.cursor()
        c.execute("""
        SELECT SUM(count_received) FROM logistics
        """)
        return str(c.fetchone())

    def sumSent(self):
        c = self._conn.cursor()
        c.execute("""
        SELECT SUM(count_sent) FROM logistics
        """)
        return str(c.fetchone())