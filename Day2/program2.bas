Option Explicit

Sub Decoration()
    'セルA1を太字にする
    Range("A1").Font.Bold = True
    
    'Pmaxセルの背景を黄色にする
    Cells(2, 6).Interior.ColorIndex = 6
    'FFセルの背景を黄色にする
    Cells(3, 6).Interior.ColorIndex = 6
    'ηセルの背景を黄色にする
    Cells(4, 6).Interior.ColorIndex = 6
End Sub
