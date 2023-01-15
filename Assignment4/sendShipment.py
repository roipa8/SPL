from Repo import r


def sendShip(location, amount):
    changeDemand = r.clinics.find(location)
    r.clinics.update(changeDemand.location, amount)
    changeLog = r.logistics.find(changeDemand.logistic)
    r.logistics.updateSent(changeLog.id,amount)
    while(int(amount)>0):
        toReduce = r.vaccines.findOldest()
        if(toReduce.quantity>=int(amount)):
            r.vaccines.orderByDate()
            r.vaccines.reduceAmount(int(amount), toReduce.id)
            amount = 0
            r.vaccines.delete()
        else:
            r.vaccines.orderByDate()
            tmp = toReduce.quantity
            r.vaccines.reduceToZero(toReduce.id)
            r.vaccines.delete()
            amount = int(amount) - int(tmp)
    return r.sum()


