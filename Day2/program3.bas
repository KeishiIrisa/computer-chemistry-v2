Option Explicit

Sub CalculateP()
    'A列7行目のセルを選択
    Cells(7, 1).Select
    ' A列のセルが空白になるまでループを繰り返す
    Do Until ActiveCell.Value = ""
        'C列にA*Bの計算結果を出力する
        ActiveCell.Offset(0, 2).Value = ActiveCell.Value * ActiveCell.Offset(0, 1).Value
        With ActiveCell
            .Offset(1, 0).Select
        End With
    Loop
End Sub
