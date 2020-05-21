Public Class 注册

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        登录.Show()
        Me.Close()
    End Sub '取消注册返回登录界面

    Private Sub TextBox2_LostFocus(sender As Object, e As EventArgs) Handles TextBox2.LostFocus
        If Len(TextBox2.Text) <= 6 Then
            Label5.ForeColor = Color.Red
            Label5.Text = "密码过于简单"
            Label5.Visible = True
        Else
            Label5.ForeColor = Color.Green
            Label5.Text = "密码可用"
            Label5.Visible = True
        End If
    End Sub '检验密码是否过于简单
    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Dim str As String = ""
        If Not TextBox1.Text = "" And Not TextBox2.Text = "" And Not TextBox3.Text = "" Then '判断是否符合注册条件
            If Label1.ForeColor = Color.Red Or Label2.ForeColor = Color.Red Or Label3.ForeColor = Color.Red Then
                MsgBox("请更正信息后注册！")
                Exit Sub
            End If
        Else
            If TextBox1.Text = "" Then
                str += Space(3) & "用户名"
            End If
            If TextBox2.Text = "" Then
                str += Space(3) & "密码"
            End If
            If TextBox3.Text = "" Then
                str += Space(3) & "确认密码"
            End If
            MsgBox("请输入" & str)
            Exit Sub
        End If
        '开始录入信息
        Dim userinfo As userinfo, newuser As user, fileno As Integer
        fileno = FreeFile()
        FileOpen(fileno, "user.txt", OpenMode.Random, , , 1024) '—————————open
        FileGet(fileno, userinfo, 1)
        userinfo.num += 1
        newuser.NO = userinfo.num '给用户编号
        newuser.name = TextBox1.Text '录入用户名
        newuser.password = TextBox2.Text '录入密码
        newuser.reservation1 = 0
        newuser.reservation2 = ""
        newuser.reservation3 = ""
        FilePut(fileno, newuser, userinfo.num + 1) '写入用户信息
        FilePut(fileno, userinfo, 1) '写入用户信息的信息
        FileClose(fileno) '----------------------------------------------------------close
        fileno = FreeFile()
        '创建相应的成绩信息
        Dim newscore As score, examinfo As examinfo, cha, ti, sumorf, max As Integer
        FileOpen(fileno, "exam.txt", OpenMode.Random, , , 1024) '打开题目文件获取题目数量信息-----open
        FileGet(fileno, examinfo, 1)
        FileClose(fileno) '------------------------------------------------------------------------close
        For cha = 1 To examinfo.chapter
            If max < examinfo.eachnum(cha) Then max = examinfo.eachnum(cha)
        Next
        newscore.NO = newuser.NO '信息：编号
        ReDim newscore.exam(examinfo.chapter, max)
        For cha = 1 To examinfo.chapter
            For ti = 1 To examinfo.eachnum(cha)

                newscore.exam(cha, ti).alldone = 0 '信息单人每道题目信息
                newscore.exam(cha, ti).falsedone = 0
            Next
        Next
        newscore.reservation1 = 0
        newscore.reservation2 = ""
        fileno = FreeFile()
        FileOpen(fileno, "score.txt", OpenMode.Random, , , 1024) '---------open
        FilePut(fileno, newscore, newscore.NO + 1)
        FileClose(fileno) '-------------------------------------------------close
        登录.Show()
        Me.Close()
    End Sub '判断是否满足注册条件，如果满足则进行注册

    Private Sub TextBox1_LostFocus(sender As Object, e As EventArgs) Handles TextBox1.LostFocus
        Dim fileno, userno As Integer, user As user, userinfo As userinfo
        If Len(TextBox1.Text) > 12 Then
            Label4.ForeColor = Color.Red
            Label4.Text = "用户名过长"
            Label4.Visible = True
            Exit Sub
        End If
        If TextBox1.Text <> "" Then '如果输入用户名，检验是否重复
            fileno = FreeFile()
            userno = 1
            FileOpen(fileno, "user.txt", OpenMode.Random, , , 1024)
            FileGet(fileno, userinfo, 1)
            Do Until userno > userinfo.num
                FileGet(fileno, user, userno + 1)
                If user.name = TextBox1.Text Then
                    Label4.ForeColor = Color.Red
                    Label4.Text = "用户名已存在"
                    Label4.Visible = True
                End If
                userno += 1
            Loop
            FileClose(fileno)
            Label4.ForeColor = Color.Green
            Label4.Text = "用户名可用"
            Label4.Visible = True
        End If
    End Sub '检验用户名是否重复

    Private Sub TextBox3_LostFocus(sender As Object, e As EventArgs) Handles TextBox3.LostFocus
        If Not TextBox2.Text = TextBox3.Text Then
            Label6.ForeColor = Color.Red
            Label6.Text = "与密码不一致"
            Label6.Visible = True
        Else
            Label6.Visible = False
        End If
    End Sub '验证确认密码与密码是否一致

End Class
