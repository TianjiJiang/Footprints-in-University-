Public Class 统计_用户_

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click

    End Sub

    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click

    End Sub

    Private Sub Button5_Click(sender As Object, e As EventArgs) Handles Button5.Click
        Label1.Visible = True
        Label2.Visible = True
        Label3.Visible = True
        Label4.Visible = True
        Label5.Visible = True
        Label6.Visible = True
        Dim g As Graphics = Me.CreateGraphics
        Dim wrongpen As New SolidBrush(Color.Red)
        Dim rightpen As New SolidBrush(Color.Green)
        Dim nopen As New SolidBrush(Color.Gray)
        Dim rightti(), wrongti(), i, j As Integer '计数
        ReDim rightti(nowexaminfo.chapter)
        ReDim wrongti(nowexaminfo.chapter)
        For i = 1 To nowexaminfo.chapter
            For j = 1 To nowexaminfo.eachnum(i)
                If nowscore.exam(i, j).alldone <> 0 Then
                    rightti(i) += nowscore.exam(i, j).alldone - nowscore.exam(i, j).falsedone
                    wrongti(i) += nowscore.exam(i, j).falsedone
                End If
            Next
        Next
        Dim r, w, n As Single '计算长度
        For i = 1 To nowexaminfo.chapter
            r = rightti(i) / nowexaminfo.eachnum(i)
            w = wrongti(i) / nowexaminfo.eachnum(i)
            n = (nowexaminfo.eachnum(i) - rightti(i) - wrongti(i)) / nowexaminfo.eachnum(i)
            r = (Button3.Location.X - Label1.Location.X - Label1.Size.Width - 150) * r
            w = (Button3.Location.X - Label1.Location.X - Label1.Size.Width - 150) * w
            n = (Button3.Location.X - Label1.Location.X - Label1.Size.Width - 150) * n
            g.FillRectangle(rightpen, Label1.Location.X + Label1.Size.Width, Label1.Location.Y + Label1.Size.Height * (i - 1), r, Label1.Size.Height - 5)
            g.FillRectangle(wrongpen, Label1.Location.X + Label1.Size.Width + r, Label1.Location.Y + Label1.Size.Height * (i - 1), w, Label1.Size.Height - 5)
            g.FillRectangle(nopen, Label1.Location.X + Label1.Size.Width + r + w, Label1.Location.Y + Label1.Size.Height * (i - 1), n, Label1.Size.Height - 5)
        Next

    End Sub

    Private Sub Button1_MouseEnter(sender As Object, e As EventArgs) Handles Button1.MouseEnter
        Button1.Visible = False
        Button3.Visible = True
        Button5.Visible = True
    End Sub

    Private Sub 统计_用户__MouseMove(sender As Object, e As MouseEventArgs) Handles Me.MouseMove
        If e.X < Button3.Location.X Or e.Y < Button3.Location.Y Or e.X > Button5.Location.X + Button5.Size.Width Or e.Y > Button5.Size.Height Then
            Button1.Visible = True
            Button3.Visible = False
            Button5.Visible = False
        End If
    End Sub
End Class