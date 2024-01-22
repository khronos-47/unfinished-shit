import difflib as df
bd = {}

def init(l): 
	file = open (l, "r", encoding='utf-8')
	index = -1
	for i in file:
		for j in i.split():
			if index == -1:
				index = int(j)
				continue 
			j = j.lower()
			try:
				bd[j].append(index)
			except:
				bd[j] = [index]
		index = -1
	print(bd.keys())
	file.close()

def search(l):
	s = {}
	for i in  l.split():
		for j in bd.keys():
			dif = df.SequenceMatcher(None, i, j ).ratio()
			print(i , j , i in j , dif)

			if dif > 0.75:
				for ii in bd[j]:
					try:
						s[ii] = s[ii] + 1
					except:
						s[ii] = 1 
	sor = sorted(s.items() , key = lambda item: item[1], reverse = True )
	return [i[0] for i in sor]

way  = "C:/Users/chron/OneDrive/Рабочий стол/qe/"
init(f'{way}datavideo.txt')
init(f'{way}dataweb.txt')
init(f'{way}datadocument.txt')
print(search('pytohn'))