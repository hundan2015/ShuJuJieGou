import openpyxl
def deal(name):
    tb=openpyxl.load_workbook("JD"+name+'.xlsx')
    sheet=tb[name]
    PNow=""
    for i in sheet.values:
        if str(i[0])!=PNow:
            PNow=str(i[0])
            sheetNow=tb.create_sheet(str(i[0]))
            sheetNow.append(i)
        else:
            sheetNow.append(i)
    tb.save(name+"newJD"+".xlsx")
for i in range(2017,2022):
    deal(str(i))