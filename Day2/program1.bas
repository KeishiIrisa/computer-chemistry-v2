Option Explicit

Sub OutputGreeting()
    `名前を定義する
    Dim name AS String
    name = "Keishi Irisa"
    `枠組みの長さを定義する
    Dim line AS Integer
    line = Len(name) + 2
    
    `枠組みを作成し、真ん中に名前を出力する
    Debug.Print String(line, "*")
    Debug.Print "* " & name & " *"
    Debug.Print String(line, "*")
End Sub
