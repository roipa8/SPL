import sys
import re
from DaoDto import Vaccine, Clinic, Supplier, Logistic
from Repo import r
from receiveShipment import recShip
from sendShipment import sendShip


def main(args):
    r.create_tables()
    with open(args[1], encoding='utf-8') as config:
        lst = config.readline().split(',')
        numOfVaccines = lst[0]
        numOfSuppliers = lst[1]
        numOfClinics = lst[2]
        numOfLogistics = lst[3]
        sum = int(numOfVaccines) + int(numOfSuppliers) + int(numOfClinics) + int(numOfLogistics) + 1
        linesOfSup = sum - (int(numOfSuppliers) + int(numOfClinics) + int(numOfLogistics) + 1)
        linesOfClin = sum - (int(numOfClinics) + int(numOfLogistics) + 1)
        linesOfLog = sum - (int(numOfLogistics) + 1)

        for i in range(1, linesOfSup + 1):
            lst = config.readline().split(',')
            r.vaccines.insert(Vaccine(lst[0], lst[1], lst[2], lst[3]))

        for i in range(linesOfSup + 2, linesOfClin + 2):
            lst = config.readline().split(',')
            r.suppliers.insert(Supplier(lst[0], lst[1], lst[2]))

        for i in range(linesOfClin + 3, linesOfLog + 3):
            lst = config.readline().split(',')
            r.clinics.insert(Clinic(lst[0], lst[1], lst[2], lst[3]))

        for i in range(linesOfLog + 4, int(sum) + 3):
            lst = config.readline().split(',')
            r.logistics.insert(Logistic(lst[0], lst[1], lst[2], lst[3]))

    toSum =""
    with open(args[2], encoding='utf-8') as orders:
        for line in orders:
            lst = line.split(',')
            if len(lst) == 3:
                sum = recShip(lst[0], lst[1], lst[2])
                toSum = toSum + sum +"\n"
            else:
                sum = sendShip(lst[0], lst[1])
                toSum = toSum + sum +"\n"
    with open(args[3], "w") as output:
        toSum = re.sub('[()]| ','',toSum)
        output.write(toSum)


if __name__ == '__main__':
    main(sys.argv)
