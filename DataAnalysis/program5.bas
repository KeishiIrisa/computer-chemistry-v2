Option Explicit

Sub IVSummary()
    ' 変数の宣言をする
    Dim summary As Worksheet
    Dim sample_sheet As Worksheet
    Dim num_sheet As Integer
    Dim n As Integer
    
    ' "IVSummary"シートを参照する
    Set summary = ThisWorkbook.Worksheets("IVSummary")
    summary.Select
    With summary
        ' ヘッダーを出力する
        .Cells(1, 1).Value = "name"
        .Cells(1, 2).Value = "Pmax [W/cm2]"
        .Cells(1, 3).Value = "FF"
        .Cells(1, 4).Value = "n [%]"
    End With

    ' 入力を開始する行を、変数を使って定義する
    n = 1
    For num_sheet = 1 To Worksheets.Count - 1
        Set sample_sheet = Worksheets(num_sheet)
        With summary
            ' シート名を出力する
            .Cells(n + 1, 1).Value = sample_sheet.Range("B1").Value
            ' Pmaxを出力する
            .Cells(n + 1, 2).Value = sample_sheet.Range("F2").Value
            ' FFを出力する
            .Cells(n + 1, 3).Value = sample_sheet.Range("F3").Value
            ' ηを出力する
            .Cells(n + 1, 4).Value = sample_sheet.Range("F4").Value
        End With
        ' 次の行に移動する
        n = n + 1
    Next num_sheet
End Sub
