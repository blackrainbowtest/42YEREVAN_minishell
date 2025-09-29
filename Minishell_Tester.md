———————————— builtins
Test   1: ✅ echo hello world 
Test   2: ✅ echo "hello world" 
Test   3: ✅ echo 'hello world' 
Test   4: ✅ echo hello'world' 
Test   5: ✅ echo hello""world 
Test   6: ✅ echo '' 
Test   7: ✅ echo "$PWD" 
Test   8: ✅ echo '$PWD' 
Test   9: ✅ echo "aspas ->'" 
Test  10: ✅ echo "aspas -> ' " 
Test  11: ✅ echo 'aspas ->"' 
Test  12: ✅ echo 'aspas -> " ' 
Test  13: ✅ echo "> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<" 
Test  14: ✅ echo '> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<' 
Test  15: ✅ echo "exit_code ->$? user ->$USER home -> $HOME" 
Test  16: ✅ echo 'exit_code ->$? user ->$USER home -> $HOME' 
Test  17: ✅ echo "$" 
Test  18: ✅ echo '$' 
Test  19: ✅ echo $ 
Test  20: ✅ echo $? 
Test  21: ✅ echo $?HELLO 
Test  22: ✅ pwd 
Test  23: ✅ pwd oi 
Test  24: ✅ export hello 
Test  25: ✅ export HELLO=123 
Test  26: ✅ export A- 
Test  27: ✅ export HELLO=123 A 
Test  28: ✅ export HELLO="123 A-" 
Test  29: ✅ export hello world 
Test  30: ✅ export HELLO-=123 
Test  31: ✅ export = 
Test  32: ✅ export 123 
Test  33: ✅ unset 
Test  34: ✅ unset HELLO 
Test  35: ✅ unset HELLO1 HELLO2 
Test  36: ✅ unset HOME 
Test  37: ✅ unset PATH 
Test  38: ✅ unset SHELL 
Test  39: ✅ cd $PWD 
Test  40: ✅ cd $PWD hi 
Test  41: ✅ cd 123123 
Test  42: ✅ exit 123 
Test  43: ✅ exit 298 
Test  44: ✅ exit +100 
Test  45: ✅ exit "+100" 
Test  46: ✅ exit +"100" 
Test  47: ✅ exit -100 
Test  48: ✅ exit "-100" 
Test  49: ✅ exit -"100" 
Test  50: ✅ exit hello 
Test  51: ✅ exit 42 world 
Test  52: ✅  
———————————— pipes
Test  53: ✅ env | sort | grep -v SHLVL | grep -v ^_ 
Test  54: ✅ cat ./test_files/infile_big | grep oi 
Test  55: ❌ cat minishell.h | grep ");"$ 
mini exit code = 139
bash exit code = 1
mini error = ()
bash error = ( No such file or directory)
Test  56: ❌ export GHOST=123 | env | grep GHOST 
mini exit code = 0
bash exit code = 1
———————————— redirects
Test  57: ❌ grep hi <./test_files/infile 
mini output = ()
bash output = (hi)
mini exit code = 1
bash exit code = 0
mini error = ( ./test_files/infile)
bash error = ()
Test  58: ❌ grep hi "<infile" <         ./test_files/infile 
mini exit code = 1
bash exit code = 2
mini error = ( ./test_files/infile)
bash error = ( No such file or directory)
Test  59: ❌ echo hi < ./test_files/infile bye bye 
mini output = ()
bash output = (hi bye bye)
mini exit code = 1
bash exit code = 0
mini error = ( ./test_files/infile)
bash error = ()
Test  60: ❌ grep hi <./test_files/infile_big <./test_files/infile 
mini output = ()
bash output = (hi)
mini exit code = 1
bash exit code = 0
mini error = ( ./test_files/infile_big)
bash error = ()
Test  61: ❌ echo <"./test_files/infile" "bonjour       42" 
mini output = ()
bash output = (bonjour 42)
mini exit code = 2
bash exit code = 0
mini error = ( syntax error near redirection unexpected token)
bash error = ()
Test  62: ❌ cat <"./test_files/file name with spaces" 
mini output = ()
bash output = (😈 😈 😈 This will break your minishell 😈 😈 😈)
mini exit code = 2
bash exit code = 0
mini error = ( syntax error near redirection unexpected token)
bash error = ()
Test  63: ❌ cat <./test_files/infile_big ./test_files/infile 
mini output = ()
bash output = (hi hello world 42)
mini exit code = 1
bash exit code = 0
mini error = ( ./test_files/infile_big)
bash error = ()
Test  64: ❌ cat <"1""2""3""4""5" 
mini exit code = 2
bash exit code = 1
mini error = ( syntax error near redirection unexpected token)
bash error = ( No such file or directory)
Test  65: ❌ echo <"./test_files/infile" <missing <"./test_files/infile" 
mini exit code = 2
bash exit code = 1
mini error = ( syntax error near redirection unexpected token)
bash error = ( No such file or directory)
Test  66: ❌ echo <missing <"./test_files/infile" <missing 
mini exit code = 2
bash exit code = 1
mini error = ( syntax error near redirection unexpected token)
bash error = ( No such file or directory)
Test  67: ❌ cat <"./test_files/infile" 
mini output = ()
bash output = (hi hello world 42)
mini exit code = 2
bash exit code = 0
mini error = ( syntax error near redirection unexpected token)
bash error = ()
Test  68: ❌ echo <"./test_files/infile_big" | cat <"./test_files/infile" 
mini output = ()
bash output = (hi hello world 42)
mini exit code = 2
bash exit code = 0
mini error = ( syntax error near redirection unexpected token)
bash error = ()
Test  69: ❌ echo <"./test_files/infile_big" | cat "./test_files/infile" 
mini output = ()
bash output = (hi hello world 42)
mini exit code = 2
bash exit code = 0
mini error = ( syntax error near redirection unexpected token)
bash error = ()
Test  70: ❌ echo <"./test_files/infile_big" | echo <"./test_files/infile" 
mini exit code = 2
bash exit code = 0
mini error = ( syntax error near redirection unexpected token)
bash error = ()
Test  71: ❌ echo hi | cat <"./test_files/infile" 
mini output = ()
bash output = (hi hello world 42)
mini exit code = 2
bash exit code = 0
mini error = ( syntax error near redirection unexpected token)
bash error = ()
Test  72: ✅ echo hi | cat "./test_files/infile" 
Test  73: ❌ cat <"./test_files/infile" | echo hi 
mini output = ()
bash output = (hi)
mini exit code = 2
bash exit code = 0
mini error = ( syntax error near redirection unexpected token)
bash error = ( Broken pipe)
Test  74: ❌ cat <"./test_files/infile" | grep hello 
mini output = ()
bash output = (hello)
mini exit code = 2
bash exit code = 0
mini error = ( syntax error near redirection unexpected token)
bash error = ()
Test  75: ❌ cat <"./test_files/infile_big" | echo hi 
mini output = ()
bash output = (hi)
mini exit code = 2
bash exit code = 0
mini error = ( syntax error near redirection unexpected token)
bash error = ( Broken pipe)
Test  76: ✅⚠️  cat <missing 
mini error = ( missing)
bash error = ( No such file or directory)
Test  77: ✅⚠️  cat <missing | cat 
mini error = ( missing)
bash error = ( No such file or directory)
Test  78: ✅⚠️  cat <missing | echo oi 
mini error = ( missing)
bash error = ( No such file or directory)
Test  79: ❌ cat <missing | cat <"./test_files/infile" 
mini output = ()
bash output = (hi hello world 42)
mini exit code = 2
bash exit code = 0
mini error = ( syntax error near redirection unexpected token)
bash error = ( No such file or directory)
Test  80: ✅⚠️  echo <123 <456 hi | echo 42 
mini error = ( 123)
bash error = ( No such file or directory)
Test  81: ❌ ls >./outfiles/outfile01 
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
README.md
bash.supp
bash_outfiles
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
redirects
syntax
test_files
tester
wildcards
mini exit code = 1
bash exit code = 0
mini error = ( ./outfiles/outfile01)
bash error = ()
Test  82: ❌ ls >         ./outfiles/outfile01 
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
README.md
bash.supp
bash_outfiles
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
redirects
syntax
test_files
tester
wildcards
mini exit code = 1
bash exit code = 0
mini error = ( ./outfiles/outfile01)
bash error = ()
Test  83: ❌ echo hi >         ./outfiles/outfile01 bye 
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
hi bye
mini exit code = 1
bash exit code = 0
mini error = ( ./outfiles/outfile01)
bash error = ()
Test  84: ❌ ls >./outfiles/outfile01 >./outfiles/outfile02 
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
README.md
bash.supp
bash_outfiles
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
redirects
syntax
test_files
tester
wildcards
mini exit code = 1
bash exit code = 0
mini error = ( ./outfiles/outfile01)
bash error = ()
Test  85: ❌ ls >./outfiles/outfile01 >./test_files/invalid_permission 
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
mini exit code = 1
bash exit code = 0
mini error = ( ./outfiles/outfile01)
bash error = ()
Test  86: ❌ ls >"./outfiles/outfile with spaces" 
Only in ./bash_outfiles: outfile with spaces
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
README.md
bash.supp
bash_outfiles
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
redirects
syntax
test_files
tester
wildcards
mini exit code = 2
bash exit code = 0
mini error = ( syntax error near redirection unexpected token)
bash error = ()
Test  87: ❌ ls >"./outfiles/outfile""1""2""3""4""5" 
Only in ./bash_outfiles: outfile12345
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
README.md
bash.supp
bash_outfiles
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
redirects
syntax
test_files
tester
wildcards
mini exit code = 2
bash exit code = 0
mini error = ( syntax error near redirection unexpected token)
bash error = ()
Test  88: ❌ ls >"./outfiles/outfile01" >./test_files/invalid_permission >"./outfiles/outfile02" 
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
README.md
bash.supp
bash_outfiles
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
redirects
syntax
test_files
tester
wildcards
mini exit code = 2
bash exit code = 0
mini error = ( syntax error near redirection unexpected token)
bash error = ()
Test  89: ❌ ls >./test_files/invalid_permission >"./outfiles/outfile01" >./test_files/invalid_permission 
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
mini exit code = 2
bash exit code = 0
mini error = ( syntax error near redirection unexpected token)
bash error = ()
Test  90: ❌ cat <"./test_files/infile" >"./outfiles/outfile01" 
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
hi
hello
world
42
mini exit code = 2
bash exit code = 0
mini error = ( syntax error near redirection unexpected token)
bash error = ()
Test  91: ❌ echo hi >./outfiles/outfile01 | echo bye 
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
hi
mini error = ( ./outfiles/outfile01)
bash error = ()
Test  92: ❌ echo hi >./outfiles/outfile01 >./outfiles/outfile02 | echo bye 
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
hi
mini error = ( ./outfiles/outfile01)
bash error = ()
Test  93: ❌ echo hi | echo >./outfiles/outfile01 bye 
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
bye
mini exit code = 139
bash exit code = 0
Test  94: ❌ echo hi | echo bye >./outfiles/outfile01 >./outfiles/outfile02 
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
bye
mini exit code = 139
bash exit code = 0
Test  95: ❌ echo hi >./outfiles/outfile01 | echo bye >./outfiles/outfile02 
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
hi
bye
mini exit code = 139
bash exit code = 0
Test  96: ❌ echo hi >./outfiles/outfile01 >./test_files/invalid_permission | echo bye 
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
mini error = ( ./outfiles/outfile01)
bash error = ()
Test  97: ✅⚠️  echo hi >./test_files/invalid_permission | echo bye 
mini error = ( ./test_files/invalid_permission)
bash error = ()
Test  98: ❌ echo hi >./test_files/invalid_permission >./outfiles/outfile01 | echo bye 
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
hi
mini error = ( ./test_files/invalid_permission)
bash error = ()
Test  99: ❌ echo hi | echo bye >./test_files/invalid_permission 
mini exit code = 139
bash exit code = 0
Test 100: ❌ echo hi | >./outfiles/outfile01 echo bye >./test_files/invalid_permission 
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
mini exit code = 139
bash exit code = 0
Test 101: ❌ echo hi | echo bye >./test_files/invalid_permission >./outfiles/outfile01 
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
bye
mini exit code = 139
bash exit code = 0
Test 102: ❌ cat <"./test_files/infile" >./test_files/invalid_permission 
mini exit code = 2
bash exit code = 0
mini error = ( syntax error near redirection unexpected token)
bash error = ()
Test 103: ❌ cat >./test_files/invalid_permission <"./test_files/infile" 
mini exit code = 2
bash exit code = 0
mini error = ( syntax error near redirection unexpected token)
bash error = ()
Test 104: ✅⚠️  cat <missing >./outfiles/outfile01 
mini error = ( missing)
bash error = ( No such file or directory)
Test 105: ❌ cat >./outfiles/outfile01 <missing 
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
mini error = ( ./outfiles/outfile01)
bash error = ( No such file or directory)
Test 106: ✅⚠️  cat <missing >./test_files/invalid_permission 
mini error = ( missing)
bash error = ( No such file or directory)
Test 107: ✅⚠️  cat >./test_files/invalid_permission <missing 
mini error = ( ./test_files/invalid_permission)
bash error = ( No such file or directory)
Test 108: ❌ cat >./outfiles/outfile01 <missing >./test_files/invalid_permission 
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
mini error = ( ./outfiles/outfile01)
bash error = ( No such file or directory)
Test 109: ❌ ls >>./outfiles/outfile01 
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
README.md
bash.supp
bash_outfiles
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
redirects
syntax
test_files
tester
wildcards
mini exit code = 1
bash exit code = 0
mini error = ( ./outfiles/outfile01)
bash error = ()
Test 110: ❌ ls >>      ./outfiles/outfile01 
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
README.md
bash.supp
bash_outfiles
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
redirects
syntax
test_files
tester
wildcards
mini exit code = 1
bash exit code = 0
mini error = ( ./outfiles/outfile01)
bash error = ()
Test 111: ❌ ls >>./outfiles/outfile01 >./outfiles/outfile01 
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
README.md
bash.supp
bash_outfiles
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
redirects
syntax
test_files
tester
wildcards
mini exit code = 1
bash exit code = 0
mini error = ( ./outfiles/outfile01)
bash error = ()
Test 112: ❌ ls >./outfiles/outfile01 >>./outfiles/outfile01 
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
README.md
bash.supp
bash_outfiles
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
redirects
syntax
test_files
tester
wildcards
mini exit code = 1
bash exit code = 0
mini error = ( ./outfiles/outfile01)
bash error = ()
Test 113: ❌ ls >./outfiles/outfile01 >>./outfiles/outfile01 >./outfiles/outfile02 
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
README.md
bash.supp
bash_outfiles
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
redirects
syntax
test_files
tester
wildcards
mini exit code = 1
bash exit code = 0
mini error = ( ./outfiles/outfile01)
bash error = ()
Test 114: ❌ ls >>./outfiles/outfile01 >>./outfiles/outfile02 
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
README.md
bash.supp
bash_outfiles
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
redirects
syntax
test_files
tester
wildcards
mini exit code = 1
bash exit code = 0
mini error = ( ./outfiles/outfile01)
bash error = ()
Test 115: ❌ ls >>./test_files/invalid_permission 
mini exit code = 1
bash exit code = 0
mini error = ( ./test_files/invalid_permission)
bash error = ()
Test 116: ❌ ls >>./test_files/invalid_permission >>./outfiles/outfile01 
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
README.md
bash.supp
bash_outfiles
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
redirects
syntax
test_files
tester
wildcards
mini exit code = 1
bash exit code = 0
mini error = ( ./test_files/invalid_permission)
bash error = ()
Test 117: ❌ ls >>./outfiles/outfile01 >>./test_files/invalid_permission 
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
mini exit code = 1
bash exit code = 0
mini error = ( ./outfiles/outfile01)
bash error = ()
Test 118: ❌ ls >./outfiles/outfile01 >>./test_files/invalid_permission >>./outfiles/outfile02 
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
README.md
bash.supp
bash_outfiles
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
redirects
syntax
test_files
tester
wildcards
mini exit code = 1
bash exit code = 0
mini error = ( ./outfiles/outfile01)
bash error = ()
Test 119: ✅⚠️  ls <missing >>./test_files/invalid_permission >>./outfiles/outfile02 
mini error = ( missing)
bash error = ( No such file or directory)
Test 120: ❌ ls >>./test_files/invalid_permission >>./outfiles/outfile02 <missing 
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
mini error = ( ./test_files/invalid_permission)
bash error = ( No such file or directory)
Test 121: ❌ echo hi >>./outfiles/outfile01 | echo bye 
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
hi
mini error = ( ./outfiles/outfile01)
bash error = ()
Test 122: ❌ echo hi >>./outfiles/outfile01 >>./outfiles/outfile02 | echo bye 
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
hi
mini error = ( ./outfiles/outfile01)
bash error = ()
Test 123: ❌ echo hi | echo >>./outfiles/outfile01 bye 
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
bye
mini error = ( ./outfiles/outfile01)
bash error = ()
Test 124: ❌ echo hi | echo bye >>./outfiles/outfile01 >>./outfiles/outfile02 
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
bye
mini exit code = 139
bash exit code = 0
Test 125: ❌ echo hi >>./outfiles/outfile01 | echo bye >>./outfiles/outfile02 
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
hi
bye
mini exit code = 139
bash exit code = 0
Test 126: ✅⚠️  echo hi >>./test_files/invalid_permission | echo bye 
mini error = ( ./test_files/invalid_permission)
bash error = ()
Test 127: ❌ echo hi >>./test_files/invalid_permission >./outfiles/outfile01 | echo bye 
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
hi
mini error = ( ./test_files/invalid_permission)
bash error = ()
Test 128: ❌ echo hi | echo bye >>./test_files/invalid_permission 
mini exit code = 139
bash exit code = 0
Test 129: ❌ echo hi | echo >>./outfiles/outfile01 bye >./test_files/invalid_permission 
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
mini exit code = 139
bash exit code = 0
Test 130: ✅⚠️  cat <minishell.h>./outfiles/outfile 
mini error = ( minishell.h)
bash error = ( No such file or directory)
Test 131: ✅⚠️  cat <minishell.h|ls 
mini error = ( minishell.h)
bash error = ( No such file or directory)
———————————— extras
Test 132: ✅  
Test 133: ❌ $PWD 
mini exit code = 0
bash exit code = 126
mini error = ( Permission denied)
bash error = ( Is a directory)
Test 134: ✅ $EMPTY 
Test 135: ❌ $EMPTY echo hi 
mini output = ()
bash output = (hi)
Test 136: ❌ ./test_files/invalid_permission 
mini exit code = 0
bash exit code = 126
mini error = ( command not found)
bash error = ( Permission denied)
Test 137: ❌ ./missing.out 
mini exit code = 0
bash exit code = 127
mini error = ( command not found)
bash error = ( No such file or directory)
Test 138: ❌ missing.out 
mini exit code = 0
bash exit code = 127
Test 139: ❌ "aaa" 
mini exit code = 0
bash exit code = 127
Test 140: ❌ test_files 
mini exit code = 0
bash exit code = 127
Test 141: ❌ ./test_files 
mini exit code = 0
bash exit code = 126
mini error = ( Permission denied)
bash error = ( Is a directory)
Test 142: ❌ /test_files 
mini exit code = 0
bash exit code = 127
mini error = ( command not found)
bash error = ( No such file or directory)
Test 143: ❌ minishell.h 
mini exit code = 0
bash exit code = 127
Test 144: ❌ $ 
mini exit code = 0
bash exit code = 127
Test 145: ❌ $? 
mini exit code = 0
bash exit code = 127
Test 146: ❌ README.md 
mini exit code = 0
bash exit code = 2
mini error = ( Exec format error)
bash error = ( command not found)
69/146
😭 😭 😭