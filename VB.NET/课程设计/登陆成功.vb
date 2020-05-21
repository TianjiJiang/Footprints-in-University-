Public Class 登陆成功
    Dim a, b, c As Single
    Private Sub 登陆成功_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Dim fileno As Integer
        Label1.Text = "亲爱的" & nowuser.name & "你好！"
        '获取成绩信息
        fileno = FreeFile()
        FileOpen(fileno, "score.txt", OpenMode.Random, , , 1024) '------------------open
        FileGet(fileno, nowscore, nowuser.NO + 1)
        FileClose(fileno) '----------------------------------------------------------close
        '获取试题信息
        fileno = FreeFile()
        FileOpen(fileno, "exam.txt", OpenMode.Random, , , 1024) '------------------open
        FileGet(fileno, nowexaminfo, 1)
        FileClose(fileno) '----------------------------------------------------------close
        '扫描用户所做题目及错题
        Dim sumall, sumall2, sumf, cha, ti As Integer, str As String
        For cha = 1 To nowexaminfo.chapter
            For ti = 1 To nowexaminfo.eachnum(cha)
                If nowscore.exam(cha, ti).alldone <> 0 Then
                    sumall +=1
                    sumall2 += nowscore.exam(cha, ti).alldone
                    sumf += nowscore.exam(cha, ti).falsedone
                End If
            Next
        Next
        str = "你已经做了" & sumall.ToString & "道题目" & vbCrLf & "正确率为" & Format(sumf / sumall2, "p")
        If sumall < nowexaminfo.sum Then str += vbCrLf & "你还有" & nowexaminfo.sum - sumall & "道未做题目"
        Label2.Text = str
    End Sub '问候语及成绩信息，试题信息

    Private Sub Button12_Click(sender As Object, e As EventArgs) Handles Button12.Click
        If MsgBox("你是否确定退出？", MsgBoxStyle.Question + MsgBoxStyle.OkCancel) = MsgBoxResult.Ok Then
            登录.Show()
            Me.Close()
        End If
    End Sub '退出登录

    Private Sub Button4_Click(sender As Object, e As EventArgs) Handles Button4.Click
        chapterselected = 1
        chapterselectednno = -1
        答题.Show()
        Me.Close()
    End Sub '进入第一章

    Private Sub Button5_Click(sender As Object, e As EventArgs) Handles Button5.Click
        chapterselected = 2
        chapterselectednno = -1
        答题.Show()
        Me.Close()
    End Sub '进入第二章

    Private Sub Button6_Click(sender As Object, e As EventArgs) Handles Button6.Click
        chapterselected = 3
        chapterselectednno = -1
        答题.Show()
        Me.Close()
    End Sub '进入第三章

    Private Sub Button7_Click(sender As Object, e As EventArgs) Handles Button7.Click
        chapterselected = 4
        chapterselectednno = -1
        答题.Show()
        Me.Close()
    End Sub '进入第四章

    Private Sub Button8_Click(sender As Object, e As EventArgs) Handles Button8.Click
        chapterselected = 5
        chapterselectednno = -1
        答题.Show()
        Me.Close()
    End Sub '进入第五章

    Private Sub Button9_Click(sender As Object, e As EventArgs) Handles Button9.Click
        chapterselected = 6
        chapterselectednno = -1
        答题.Show()
        Me.Close()
    End Sub '进入第六章

    Private Sub Button10_Click(sender As Object, e As EventArgs) Handles Button10.Click
        chapterselected = 7
        chapterselectednno = -1
        答题.Show()
        Me.Close()
    End Sub '进入第七章

    Private Sub Button11_Click(sender As Object, e As EventArgs) Handles Button11.Click
        chapterselected = 8
        chapterselectednno = -1
        答题.Show()
        Me.Close()
    End Sub '进入第八章

    Private Sub Button3_MouseEnter(sender As Object, e As EventArgs) Handles Button3.MouseEnter
        Timer1.Enabled = True
    End Sub '触发显示选章节按钮

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick '动画效果====显示按钮
        Dim g As Graphics = Me.CreateGraphics
        Dim brush As New SolidBrush(Color.SkyBlue)
        Dim rect As New RectangleF(410, 131, 300, 200)
        c += 1
        If c > 50 Then
            Timer1.Enabled = False
            Exit Sub
        End If
        c += 1
        a = ((Val(Button11.Location.X + Button11.Size.Width) + 10 - Val(Button3.Location.X)) / 50) * c
        b = ((Val(Button11.Location.Y + Button11.Size.Height) + 10 - Val(Button3.Location.Y)) / 50) * c

        'Debug.Print()
        g.FillRectangle(brush, Button3.Location.X, Button3.Location.Y, a, b)
        If c = 50 Then
            Timer1.Enabled = False
            If nowexaminfo.chapter >= 1 Then
                Button4.Enabled = True
                Button4.Visible = True
            End If
            If nowexaminfo.chapter >= 2 Then
                Button5.Enabled = True
                Button5.Visible = True
            End If

            If nowexaminfo.chapter >= 3 Then
                Button6.Enabled = True
                Button6.Visible = True
            End If

            If nowexaminfo.chapter >= 4 Then
                Button7.Enabled = True
                Button7.Visible = True
            End If

            If nowexaminfo.chapter >= 5 Then
                Button8.Enabled = True
                Button8.Visible = True
            End If

            If nowexaminfo.chapter >= 6 Then
                Button9.Enabled = True
                Button9.Visible = True
            End If

            If nowexaminfo.chapter >= 7 Then
                Button10.Enabled = True
                Button10.Visible = True
            End If

            If nowexaminfo.chapter >= 8 Then
                Button11.Enabled = True
                Button11.Visible = True
            End If
        End If
    End Sub '动画效果====显示按钮

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        '扫描用户所做题目，确定做题停止点
        Dim cha, ti As Integer
        For cha = 1 To nowexaminfo.chapter
            For ti = 1 To nowexaminfo.eachnum(cha)
                If nowscore.exam(cha, ti).alldone = 0 Then
                    chapterselected = cha
                    chapterselectednno = ti
                    GoTo line1
                End If
            Next
        Next
        chapterselected = nowexaminfo.chapter
        chapterselectednno = nowexaminfo.eachnum(chapterselected)
        '=============================待补充
line1:
        答题.Show()
        Me.Close()
    End Sub '继续做题=====================有待改进

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        chapterselected = 1
        chapterselectednno = 1 '用于识别非分章练习
        答题.Show()
        Me.Close()
    End Sub '从头开始做题

    Private Sub 登陆成功_MouseMove(sender As Object, e As MouseEventArgs) Handles Me.MouseMove
        If e.X < Val(Button3.Location.X) Or e.Y < Val(Button3.Location.Y) Or e.X > Val(Button3.Location.X) + a Or e.Y > Val(Button3.Location.Y) + b Then
            Button4.Enabled = False
            Button4.Visible = False
            Button5.Enabled = False
            Button5.Visible = False
            Button6.Enabled = False
            Button6.Visible = False
            Button7.Enabled = False
            Button7.Visible = False
            Button8.Enabled = False
            Button8.Visible = False
            Button9.Enabled = False
            Button9.Visible = False
            Button10.Enabled = False
            Button10.Visible = False
            Button11.Enabled = False
            Button11.Visible = False
            Dim g As Graphics = Me.CreateGraphics
            Dim brush As New SolidBrush(Color.White)
            Dim rect As New RectangleF(Button3.Location.X, Button3.Location.Y, a, b)
            g.FillRectangle(brush, rect)
            c = 0
        End If
    End Sub '数表移开，按钮消失

    Private Sub Button13_Click(sender As Object, e As EventArgs) Handles Button13.Click
        修改密码.Show()
        Me.Close()
    End Sub '进入修改密码及界面
End Class