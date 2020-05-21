Public Class 修改密码

   
    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Dim str As String = ""
        If Not TextBox1.Text = "" And Not TextBox2.Text = "" And Not TextBox3.Text = "" Then
            If Not TextBox1.Text = nowuser.password Then '-------------------------------------------信息不正确===退出
                MsgBox("原密码输入错误！", MsgBoxStyle.Critical + MsgBoxStyle.OkOnly, "错误")
                Exit Sub
            End If
            If Len(TextBox2.Text) <= 6 Then
                MsgBox("密码过于简单", MsgBoxStyle.Critical + MsgBoxStyle.OkOnly, "错误")
                Exit Sub
            End If
            If Not TextBox2.Text = TextBox3.Text Then
                MsgBox("确认密码与新密码不同", MsgBoxStyle.Critical + MsgBoxStyle.OkOnly, "错误")
                Exit Sub
            End If
        Else
            If TextBox1.Text = "" Then '信息不全----------退出
                str += Space(3) & "原密码"
            End If
            If TextBox2.Text = "" Then
                str += Space(3) & "新密码"
            End If
            If TextBox3.Text = "" Then
                str += Space(3) & "确认密码"
            End If
            MsgBox("请输入" & str)
            Exit Sub
        End If
        '检查完毕，开始录入新信息
        nowuser.password = TextBox2.Text
        Dim fileno As Integer
        fileno = FreeFile()
        FileOpen(fileno, "user.txt", OpenMode.Random, , , 1024) '---------------open
        FilePut(fileno, nowuser, nowuser.NO + 1)
        FileClose(fileno) '------------------------------------------------------close
        登录.TextBox1.Text = nowuser.name
        登录.Show()
        Me.Close()
    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        登陆成功.Show()
        Me.Close()

    End Sub
End Class