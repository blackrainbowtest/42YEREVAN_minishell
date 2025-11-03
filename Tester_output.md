🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥
                                                                                             
 ██    ██ █ ██    █ █ █████ █   █ █████ █     █       ██████ █████ █████ ██████ █████ █████  
 ███  ███ █ ███   █ █ █     █   █ █     █     █         ██   █     █       ██   █     █   ██ 
 █ ████ █ █ █ ██  █ █ █████ █████ ████  █     █         ██   ████  █████   ██   ████  █████  
 █  ██  █ █ █  ██ █ █     █ █   █ █     █     █         ██   █         █   ██   █     █   ██ 
 █      █ █ █   ███ █ █████ █   █ █████ █████ █████     ██   █████ █████   ██   █████ █   ██ 
                                                                                             
🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥
                                                                                              
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
Test  55: ✅ cat minishell.h | grep ");"$ 
Test  56: ✅ export GHOST=123 | env | grep GHOST 
———————————— redirects
Test  57: ✅ grep hi <./test_files/infile 
Test  58: ✅ grep hi "<infile" <         ./test_files/infile 
Test  59: ✅ echo hi < ./test_files/infile bye bye 
Test  60: ✅ grep hi <./test_files/infile_big <./test_files/infile 
Test  61: ✅ echo <"./test_files/infile" "bonjour       42" 
Test  62: ✅ cat <"./test_files/file name with spaces" 
Test  63: ✅ cat <./test_files/infile_big ./test_files/infile 
Test  64: ❌ cat <"1""2""3""4""5" 
mini exit code = 2
bash exit code = 1
mini error = ( unknown redir type unexpected token)
bash error = ( No such file or directory)
Test  65: ✅⚠️  echo <"./test_files/infile" <missing <"./test_files/infile" 
mini error = ( failed to open heredoc for `missing')
bash error = ( No such file or directory)
Test  66: ✅⚠️  echo <missing <"./test_files/infile" <missing 
mini error = ( failed to open heredoc for `missing')
bash error = ( No such file or directory)
Test  67: ✅ cat <"./test_files/infile" 
Test  68: ✅ echo <"./test_files/infile_big" | cat <"./test_files/infile" 
Test  69: ✅ echo <"./test_files/infile_big" | cat "./test_files/infile" 
Test  70: ✅ echo <"./test_files/infile_big" | echo <"./test_files/infile" 
Test  71: ✅ echo hi | cat <"./test_files/infile" 
Test  72: ✅ echo hi | cat "./test_files/infile" 
Test  73: ✅⚠️  cat <"./test_files/infile" | echo hi 
mini error = ()
bash error = ( Broken pipe)
Test  74: ✅ cat <"./test_files/infile" | grep hello 
Test  75: ✅⚠️  cat <"./test_files/infile_big" | echo hi 
mini error = ()
bash error = ( Broken pipe)
Test  76: ✅⚠️  cat <missing 
mini error = ( failed to open heredoc for `missing')
bash error = ( No such file or directory)
Test  77: ✅⚠️  cat <missing | cat 
mini error = ( failed to open heredoc for `missing')
bash error = ( No such file or directory)
Test  78: ✅⚠️  cat <missing | echo oi 
mini error = ( failed to open heredoc for `missing')
bash error = ( No such file or directory)
Test  79: ✅⚠️  cat <missing | cat <"./test_files/infile" 
mini error = ( failed to open heredoc for `missing')
bash error = ( No such file or directory)
Test  80: ✅⚠️  echo <123 <456 hi | echo 42 
mini error = ( failed to open heredoc for `123')
bash error = ( No such file or directory)
Test  81: ✅ ls >./outfiles/outfile01 
Test  82: ✅ ls >         ./outfiles/outfile01 
Test  83: ✅ echo hi >         ./outfiles/outfile01 bye 
Test  84: ✅ ls >./outfiles/outfile01 >./outfiles/outfile02 
Test  85: ✅⚠️  ls >./outfiles/outfile01 >./test_files/invalid_permission 
mini error = ( failed to open heredoc for `./test_files/invalid_permission')
bash error = ( Permission denied)
Test  86: ✅ ls >"./outfiles/outfile with spaces" 
Test  87: ❌ ls >"./outfiles/outfile""1""2""3""4""5" 
Only in ./bash_outfiles: outfile12345
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
bash_outfiles
bash.supp
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
minishell_tester
os_specific
outfiles
pipes
README.md
redirects
syntax
tester
test_files
wildcards
mini exit code = 2
bash exit code = 0
mini error = ( unknown redir type unexpected token)
bash error = ()
Test  88: ✅⚠️  ls >"./outfiles/outfile01" >./test_files/invalid_permission >"./outfiles/outfile02" 
mini error = ( failed to open heredoc for `./test_files/invalid_permission')
bash error = ( Permission denied)
Test  89: ✅⚠️  ls >./test_files/invalid_permission >"./outfiles/outfile01" >./test_files/invalid_permission 
mini error = ( failed to open heredoc for `./test_files/invalid_permission')
bash error = ( Permission denied)
Test  90: ✅ cat <"./test_files/infile" >"./outfiles/outfile01" 
Test  91: ✅ echo hi >./outfiles/outfile01 | echo bye 
Test  92: ✅ echo hi >./outfiles/outfile01 >./outfiles/outfile02 | echo bye 
Test  93: ✅ echo hi | echo >./outfiles/outfile01 bye 
Test  94: ✅ echo hi | echo bye >./outfiles/outfile01 >./outfiles/outfile02 
Test  95: ✅ echo hi >./outfiles/outfile01 | echo bye >./outfiles/outfile02 
Test  96: ✅⚠️  echo hi >./outfiles/outfile01 >./test_files/invalid_permission | echo bye 
mini error = ( failed to open heredoc for `./test_files/invalid_permission')
bash error = ( Permission denied)
Test  97: ✅⚠️  echo hi >./test_files/invalid_permission | echo bye 
mini error = ( failed to open heredoc for `./test_files/invalid_permission')
bash error = ( Permission denied)
Test  98: ✅⚠️  echo hi >./test_files/invalid_permission >./outfiles/outfile01 | echo bye 
mini error = ( failed to open heredoc for `./test_files/invalid_permission')
bash error = ( Permission denied)
Test  99: ✅⚠️  echo hi | echo bye >./test_files/invalid_permission 
mini error = ( failed to open heredoc for `./test_files/invalid_permission')
bash error = ( Permission denied)
Test 100: ✅⚠️  echo hi | >./outfiles/outfile01 echo bye >./test_files/invalid_permission 
mini error = ( failed to open heredoc for `./test_files/invalid_permission')
bash error = ( Permission denied)
Test 101: ✅⚠️  echo hi | echo bye >./test_files/invalid_permission >./outfiles/outfile01 
mini error = ( failed to open heredoc for `./test_files/invalid_permission')
bash error = ( Permission denied)
Test 102: ✅⚠️  cat <"./test_files/infile" >./test_files/invalid_permission 
mini error = ( failed to open heredoc for `./test_files/invalid_permission')
bash error = ( Permission denied)
Test 103: ✅⚠️  cat >./test_files/invalid_permission <"./test_files/infile" 
mini error = ( failed to open heredoc for `./test_files/invalid_permission')
bash error = ( Permission denied)
Test 104: ✅⚠️  cat <missing >./outfiles/outfile01 
mini error = ( failed to open heredoc for `missing')
bash error = ( No such file or directory)
Test 105: ✅⚠️  cat >./outfiles/outfile01 <missing 
mini error = ( failed to open heredoc for `missing')
bash error = ( No such file or directory)
Test 106: ✅⚠️  cat <missing >./test_files/invalid_permission 
mini error = ( failed to open heredoc for `missing')
bash error = ( No such file or directory)
Test 107: ✅⚠️  cat >./test_files/invalid_permission <missing 
mini error = ( failed to open heredoc for `./test_files/invalid_permission')
bash error = ( Permission denied)
Test 108: ✅⚠️  cat >./outfiles/outfile01 <missing >./test_files/invalid_permission 
mini error = ( failed to open heredoc for `missing')
bash error = ( No such file or directory)
Test 109: ✅ ls >>./outfiles/outfile01 
Test 110: ✅ ls >>      ./outfiles/outfile01 
Test 111: ✅ ls >>./outfiles/outfile01 >./outfiles/outfile01 
Test 112: ✅ ls >./outfiles/outfile01 >>./outfiles/outfile01 
Test 113: ✅ ls >./outfiles/outfile01 >>./outfiles/outfile01 >./outfiles/outfile02 
Test 114: ✅ ls >>./outfiles/outfile01 >>./outfiles/outfile02 
Test 115: ✅⚠️  ls >>./test_files/invalid_permission 
mini error = ( failed to open heredoc for `./test_files/invalid_permission')
bash error = ( Permission denied)
Test 116: ✅⚠️  ls >>./test_files/invalid_permission >>./outfiles/outfile01 
mini error = ( failed to open heredoc for `./test_files/invalid_permission')
bash error = ( Permission denied)
Test 117: ✅⚠️  ls >>./outfiles/outfile01 >>./test_files/invalid_permission 
mini error = ( failed to open heredoc for `./test_files/invalid_permission')
bash error = ( Permission denied)
Test 118: ✅⚠️  ls >./outfiles/outfile01 >>./test_files/invalid_permission >>./outfiles/outfile02 
mini error = ( failed to open heredoc for `./test_files/invalid_permission')
bash error = ( Permission denied)
Test 119: ✅⚠️  ls <missing >>./test_files/invalid_permission >>./outfiles/outfile02 
mini error = ( failed to open heredoc for `missing')
bash error = ( No such file or directory)
Test 120: ✅⚠️  ls >>./test_files/invalid_permission >>./outfiles/outfile02 <missing 
mini error = ( failed to open heredoc for `./test_files/invalid_permission')
bash error = ( Permission denied)
Test 121: ✅ echo hi >>./outfiles/outfile01 | echo bye 
Test 122: ✅ echo hi >>./outfiles/outfile01 >>./outfiles/outfile02 | echo bye 
Test 123: ✅ echo hi | echo >>./outfiles/outfile01 bye 
Test 124: ✅ echo hi | echo bye >>./outfiles/outfile01 >>./outfiles/outfile02 
Test 125: ✅ echo hi >>./outfiles/outfile01 | echo bye >>./outfiles/outfile02 
Test 126: ✅⚠️  echo hi >>./test_files/invalid_permission | echo bye 
mini error = ( failed to open heredoc for `./test_files/invalid_permission')
bash error = ( Permission denied)
Test 127: ✅⚠️  echo hi >>./test_files/invalid_permission >./outfiles/outfile01 | echo bye 
mini error = ( failed to open heredoc for `./test_files/invalid_permission')
bash error = ( Permission denied)
Test 128: ✅⚠️  echo hi | echo bye >>./test_files/invalid_permission 
mini error = ( failed to open heredoc for `./test_files/invalid_permission')
bash error = ( Permission denied)
Test 129: ✅⚠️  echo hi | echo >>./outfiles/outfile01 bye >./test_files/invalid_permission 
mini error = ( failed to open heredoc for `./test_files/invalid_permission')
bash error = ( Permission denied)
Test 130: ✅⚠️  cat <minishell.h>./outfiles/outfile 
mini error = ( failed to open heredoc for `minishell.h')
bash error = ( No such file or directory)
Test 131: ✅⚠️  cat <minishell.h|ls 
mini error = ( failed to open heredoc for `minishell.h')
bash error = ( No such file or directory)
———————————— extras
Test 132: ✅  
Test 133: ✅ $PWD 
Test 134: ✅ $EMPTY 
Test 135: ✅ $EMPTY echo hi 
Test 136: ✅ ./test_files/invalid_permission 
Test 137: ✅ ./missing.out 
Test 138: ✅ missing.out 
Test 139: ✅ "aaa" 
Test 140: ✅ test_files 
Test 141: ✅ ./test_files 
Test 142: ✅ /test_files 
Test 143: ✅ minishell.h 
Test 144: ✅ $ 
Test 145: ✅ $? 
Test 146: ✅ README.md 
144/146
😭 😭 😭