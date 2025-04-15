Option Explicit

Sub OverlappingOperation()
    Dim day As Integer
    Dim wkday As Integer
    Dim prohr As Integer
        'バッチあたり全プロセスに4時間かかる
        prohr = 4
    Dim production As Integer
        'バッチあたり8 kg生成できるとする
        production = 2
    Dim proTot As Integer
        '日数を30日まで数える
        For day = 1 To 30
            '条件判断する変数を指定する
                Select Case day
                    Case 3, 23
                        wkday = wkday
                    Case Else
                        Select Case day Mod 7
                            Case 0, 6
                                wkday = wkday
                            Case Else 
                                wkday = wkday + 1
                        End Select
                End Select
        Next
    '最後のバッチが分離工程ができず途中で終わってしまうので、生産量に含めない
    proTot = (wkday * 24/prohr - 1) * production
    '生産量を出力する
    MsgBox proTot & " kg"
End Sub

'238kg
