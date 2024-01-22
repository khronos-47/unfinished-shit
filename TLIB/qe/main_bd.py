bdmain_video = {}
bdmain_web = {}
bdmain_document = {}
def init( ):
	print("START main_bd initialize....")
	print("reading viddeo database...")
	file = open ('C:/Users/chron/OneDrive/Рабочий стол/qe/databasevideo.txt', "r", encoding = 'utf-8')
	for i in file:
		s = i.split('||')
		for j in range(len(s)):
			if s[j][-1] == '\n':
				s[j] = s[j][:-1]
		bdmain_video[s[0]] = s[1:]
	file.close()
	print('finish')

	print('reading web database...')
	file = open('C:/Users/chron/OneDrive/Рабочий стол/qe/databaseweb.txt', "r", encoding = 'utf-8')
	for i in file:
		s = i.split('||')  
		bdmain_web[s[0]] = s[1:]
	file.close()
	print('finish')

	print('reading document database...')
	file = open('C:/Users/chron/OneDrive/Рабочий стол/qe/databasedocument.txt', "r", encoding = 'utf-8')
	for i in file:
		s =  i.split('||')
		bdmain_document[s[0]] = s[1:]
	file.close()
	print('finish')

	print('initialize end:')
	print("bdmain_document: \n" , bdmain_document)
	print("bdmain_web: \n", bdmain_web)
	print("bdmain_video: \n", bdmain_video)	


def video_inf (l):
	print(l)
	return bdmain_video[str(l)]

def document_inf (l):
	print(l)
	return bdmain_document[str(l)]

def  web_inf (l):
	print(l)
	return bdmain_web[str(l)]

def add_to_video_bd(l):
	print(l , type(l))
	file = open ('C:/Users/chron/OneDrive/Рабочий стол/qe/databasevideo.txt', "a", encoding = 'utf-8')
	file.write('\n')
	for i in l:
		file.write(f'{i} ')
	bdmain_video[l[0]] = l[1:]

def add_to_document_bd(l):
	print(l , type(l))
	file = open ('C:/Users/chron/OneDrive/Рабочий стол/qe/databasedocument.txt', "a", encoding = 'utf-8')
	file.write('\n')
	for i in l:
		file.write(f'{i} ')
	bdmain_document[l[0]] = l[1:]

def add_to_web_bd(l):
	print(l , type(l))
	file = open ('C:/Users/chron/OneDrive/Рабочий стол/qe/databaseweb.txt', "a", encoding = 'utf-8')
	file.write('\n')
	for i in l:
		file.write(f'{i} ')
	bdmain_web[l[0]] = l[1:]

init()