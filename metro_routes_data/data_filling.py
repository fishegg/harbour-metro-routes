import openpyxl

# book_file=input("input xlsx file name:")
book_file="D:\\project\\untitled1-master\\testdata\\新建 Microsoft Excel 工作表.xlsx"
wb=openpyxl.load_workbook(book_file)
sheet=wb["Sheet1"]
while(True):
	option=int(input("1=fill with 0,2=fill line grids,3=fill interchange grids,-1=quit:"))
	if(option != 1 and option != 2 and option != 3):
		exit()
	strings=[]
	#book_file="D:\\project\\ocrtest\\xlsx.xlsx"

	while(True):
		if(option==1):
			count=int(input("stations count:"))
			if(count == -1):
				break
			for row in range (1,count+1):
				for column in range (1,count+1):
					sheet.cell(row,column,0)
			wb.save(book_file)
		elif(option==2):
			terminal1=int(input("terminal 1:"))
			if(terminal1==-1):
				break
			terminal2=int(input("terminal 2:"))
			distance=int(input("distance:"))
			for row in range (terminal1,terminal2+1):
				for column in range (terminal1,terminal2+1):
					if(row==column+1 or column==row+1):
						sheet.cell(row,column,distance)
			wb.save(book_file)
		elif(option==3):
			interchange1=int(input("interchange 1:"))
			if(interchange1==-1):
				break
			interchange2=int(input("interchange 2:"))
			distance=int(input("distance:"))
			sheet.cell(interchange1,interchange2,distance)
			sheet.cell(interchange2,interchange1,distance)
			wb.save(book_file)
	wb.save(book_file)