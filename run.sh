# Copyright (c) 2024 Dmitry Petukhov AKA tepamid
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

RED='\033[0;31m'
GRN='\033[0;32m'
Cyan="\033[0;36m"
NC='\033[0m' # No Color

if [ -z "$1" ]; then
	echo 'First argument must be a task ID'
	return
fi

if [ ! -d $1 ]; then
	echo "Directory $1 does not exist"
	return
fi



cd $1

rm *.out
rm *.out.txt
rm -r a.out.*

EXECUTABLE=a.out
# g++ -O0 -std=c++11  -Wno-c++11-extensions main.cpp 
# g++ -O2 -DTEPAMID -fno-strict-aliasing -x c++ -std=c++17 -Wl, main.cpp -o $EXECUTABLE
g++ -DHOME -DTEPAMID -O2 -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -Wl,-stack_size,0x100000000 -Wl, main.cpp -o $EXECUTABLE

date;

if [ -f $EXECUTABLE ]; then
	for TESTFILENAME in ./test*; do
		echo -e "${Cyan}Run $TESTFILENAME${NC}"

		EXPECTED="${TESTFILENAME/test/gt}"
		ACTUAL="$TESTFILENAME.out.txt"

		if [ ! -f $EXPECTED ]; then
			touch $EXPECTED
		fi

		( ./$EXECUTABLE < $TESTFILENAME > $ACTUAL )

		res=$(diff -w $EXPECTED $ACTUAL)

		if diff -w $EXPECTED $ACTUAL>/dev/null; then
			echo -e "${GRN}pass $TESTFILENAME${NC}"
			rm $ACTUAL
		else
			echo -e "${RED}FAIL $TESTFILENAME${NC}"

			echo $res
		fi
	done
fi

date;

rm a.out
rm  -r a.out.*

cd ..
