Option Explicit
Sub IV_analysis()
'
' IV_analysis Macro
'

'
    Range("C6").Select
    ActiveCell.FormulaR1C1 = "P"
    Range("C7").Select
    Application.CutCopyMode = False
    ActiveCell.FormulaR1C1 = "=RC[-2]*RC[-1]"
    Range("C7").Select
    Selection.AutoFill Destination:=Range("C7:C223"), Type:=xlFillDefault
    Range("C7:C223").Select
    ActiveWindow.SmallScroll Down:=-185
    Range("E2").Select
    ActiveCell.FormulaR1C1 = "Pmax"
    Range("F2").Select
    ActiveCell.FormulaR1C1 = "=MAX(R[5]C[-3]:R[221]C[-3])"
    Range("F3").Select
    ActiveWindow.SmallScroll Down:=-2
    Range("E3").Select
    ActiveCell.FormulaR1C1 = "FF"
    Range("F3").Select
    ActiveCell.FormulaR1C1 = "=R[-1]C/(R[1]C[-4]*R[2]C[-4])"
    Range("E4").Select
    ActiveSheet.Paste
    Range("F4").Select
    Application.CutCopyMode = False
    ActiveCell.FormulaR1C1 = "=100*R[-2]C/R[-1]C[-4]"
    Range("F5").Select
End Sub
Sub IV_chart()
'
' IV_chart Macro
'

'
    Range("A7").Select
    ActiveWindow.SmallScroll Down:=220
    Range("A7:B223").Select
    ActiveWindow.SmallScroll Down:=-220
    ActiveSheet.Shapes.AddChart2 240, xlXYScatterSmoothNoMarkers
    ActiveChart.SetSourceData Source:=Range("$A$7:$B$223")
    ActiveSheet.ChartObjects(1).Chart.HasTitle = True
    ActiveSheet.ChartObjects(1).Chart.ChartTitle.Text = "IV_curve"
    ActiveChart.Axes(xlCategory, xlPrimary).HasTitle = True
    ActiveChart.Axes(xlCategory, xlPrimary).AxisTitle.Characters.Text = "Voltage (V)"
    ActiveChart.Axes(xlValue, xlPrimary).HasTitle = True
    ActiveChart.Axes(xlValue, xlPrimary).AxisTitle.Characters.Text = "Current (mA/ cm2)"
End Sub
