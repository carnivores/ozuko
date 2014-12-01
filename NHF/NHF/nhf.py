
words = { "and", "as", "assert", "break",
          "class", "continue", "def", "del",
          "elif", "else", "except", "exec",
          "finally", "for", "from", "if",
          "import", "in", "is", "lambda",
          "not", "or", "pass", "print",
          "raise", "return", "try", "while",
          "with", "yield", "global"
}


def myhash( str, scale ):
	x = 0
	for letter in str:
		x <<=3
		x ^= ord(letter)
	return (scale/x)%41

def main():

	for i in range(1948027440, 1948027450):
		#print("------------")
		print(i, end="\t");
		arr = []
		for word in words:
			h = int(myhash(word, i))
			#print(h,word)
			if h in arr:
				#print(arr, " --> ", h)
				break
			else:
				arr.append(h)
				print("adding", h, "for", word)
		if len(arr) == 31:
			print(" generates perfect hash.")
		else:
			print(" ")

if __name__ == "__main__":
	main()