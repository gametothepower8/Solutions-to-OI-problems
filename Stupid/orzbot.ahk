F1:: ; start
Loop, 1000
{
SetKeyDelay, 0
send, tmw{Space}orz{Space}%A_Index%
SetKeyDelay, 1000
send, {ENTER}
}
F2::ExitApp ; close the script
