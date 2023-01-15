from Repo import r
from DaoDto import Vaccine


def recShip(name, amount, date):
    idOfSup = r.suppliers.find(name)
    logOfSup = r.suppliers.findLogOfSup(name)
    r.vaccines.insert(Vaccine(None, date, idOfSup.id, amount))
    r.logistics.updateRec(logOfSup.logistic, amount)
    return r.sum()