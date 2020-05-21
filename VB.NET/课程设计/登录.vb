Public Class 登录

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Dim user As user, fileno1, userNO As Integer, userinfo As userinfo
        fileno1 = FreeFile()
        userNO = 1
        FileOpen(fileno1, "user.txt", OpenMode.Random, , , 1024) '--------------open
        FileGet(fileno1, userinfo, 1)
        Do Until userNO > userinfo.num
            FileGet(fileno1, user, userNO + 1)
            If user.name = TextBox1.Text Then
                If user.password = TextBox2.Text Then
                    nowuser = user
                    FileClose(fileno1) '------------------------------------------close
                    登陆成功.Show()
                    Me.Close()
                    Exit Sub
                End If
                Label3.Text = "密码错误"
                Label3.Visible = True
                FileClose(fileno1) '------------------------------------------close
                Exit Sub
            End If
            userNO += 1
        Loop
        FileClose(fileno1) '----------------------------------------------------close
        Label3.Text = "很抱歉，用户不存在"
        Label3.Visible = True
    End Sub '验证用户名及密码

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        注册.Show()
        Me.Close()
    End Sub '进入注册界面

    Private Sub 登录_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        TextBox1.Text = nowuser.name
    End Sub
End Class