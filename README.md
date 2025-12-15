# Minishell
Write a shell

Ex command:
-	echo "salut
-	echo "sa'lut"

- 	echo "'salut'"
- 	echo ""
-	echo ''
- 	echo "		"
-	echo "sa"lut

-	echo $USER$PATH
-	echo "$USER"
-	echo '$USER'
-	echo $UNDEFINED
-	echo "$?"
-	echo a$?b

-	| ls
-	ls || wc
-	ls | | wc
-	ls |
-	ehco test |grep t

< log.txt cat | grep "error" | wc > error.txt -l

git rebase (NAME)

#		#		#		#		#		#		#		#		#		#		#		#		#
		Exit status 0	(success)

-	executed successfully

#-----------------------------------------------------------------------------------------------#
#		#		#		#		#		#		#		#		#		#		#		#		#
		Exit status 1	(Permission denied)

-	Although the command's output looks as though everything went well, if you scroll up you will see several "Permission denied" errors in the listing. These errors result in an exit status of 1, which is described as "impermissible operations." Although you might expect that a "Permission denied" error leads to an exit status of 1, you'd be wrong, as you will see in the next section. 

#-----------------------------------------------------------------------------------------------#
#		#		#		#		#		#		#		#		#		#		#		#		#
		Exit status 2	(Permission problem)

-	Exit status 2 appears when there's a permissions problem or a missing keyword in a command or script

#-----------------------------------------------------------------------------------------------#
#		#		#		#		#		#		#		#		#		#		#		#		#
		Exit status 126	(Permission Error)

-	Exit status 126 is an interesting permissions error code. The easiest way to demonstrate when this code appears is to create a script file and forget to give that file execute permission

#-----------------------------------------------------------------------------------------------#
#		#		#		#		#		#		#		#		#		#		#		#		#
		Exit status 127 (Command doesn't exist)

-	Exit status 127 tells you that one of two things has happened: Either the command doesn't exist, or the command isn't in your path ($PATH). This code also appears if you attempt to execute a command that is in your current working directory.
#-----------------------------------------------------------------------------------------------#
#		#		#		#		#		#		#		#		#		#		#		#		#
		Exit status 128

-	Exit status 128 is the response received when an out-of-range exit code is used in programming. From my experience, exit status 128 is not possible to produce.
#-----------------------------------------------------------------------------------------------#
#		#		#		#		#		#		#		#		#		#		#		#		#
		Exit status 130	(Exit program with CTR-C)

-	If you're running a program or script and press Ctrl-C to stop it, your exit status is 130. This status is easy to demonstrate. Issue ls -lR / and then immediately press Ctrl-C:

#-----------------------------------------------------------------------------------------------#
#		#		#		#		#		#		#		#		#		#		#		#		#
		Exit status 255

-	This final reserved exit status is easy to produce but difficult to interpret. The documentation that I've found states that you receive exit status 255 if you use an exit code that's out of the range 0-255.