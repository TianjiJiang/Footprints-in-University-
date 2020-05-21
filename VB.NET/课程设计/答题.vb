Public Class 答题
    Structure tempexamstatistics
        Dim chap As Integer '章节
        Dim ti As Integer '章节内题目
        Dim ans As String '用户所选
        Dim key As String '答案
    End Structure '临时统计结构
    Dim cha, ti As Integer '题目定位
    Dim tempexam As exam '当前题目信息
    Dim statistics() As tempexamstatistics '用户答题统计
    Dim nows As Integer '当前题目所对临时记录空间
    Dim starttime As Date '进入答题界面时间
    Dim oldcha, oldti As Integer '保存原来数据
    Dim ifinitialize As Boolean = True '选项改变是否为初始化
    Sub doornotremindercover()
        Dim g As Graphics = Me.CreateGraphics
        Dim nonpen As New SolidBrush(Color.White)
        Dim havepen As New SolidBrush(Color.MediumSpringGreen)
        Dim haventpen As New SolidBrush(Color.LightSalmon)
        Dim olddoingpen As New Pen(Brushes.AntiqueWhite, 5)
        Dim font As New Font("幼圆", 15)
        Dim x, y, i, j, n, h, w As Single
        ifinitialize = True '--------------
        A.Checked = False
        ifinitialize = True '--------------
        B.Checked = False
        ifinitialize = True '--------------
        C.Checked = False
        ifinitialize = True '--------------
        D.Checked = False
        ifinitialize = True '--------------
        OE.Checked = False
        ifinitialize = False  '--------------
        n = 0
        h = ((Val(Button2.Location.X) + Val(Button2.Size.Width)) - Val(Button1.Location.X)) / 6
        w = h
        For j = 0 To Math.Ceiling((nowexaminfo.eachnum(cha) / 5))
            For i = 0 To 4
                n += 1
                x = Val(Button1.Location.X) + ((Val(Button2.Location.X) + Val(Button2.Size.Width)) - Val(Button1.Location.X)) / 60 + i * ((Val(Button2.Location.X) + Val(Button2.Size.Width)) - Val(Button1.Location.X)) / 5
                y = Val(Label2.Location.Y) + ((Val(Button2.Location.X) + Val(Button2.Size.Width)) - Val(Button1.Location.X)) / 60 + j * ((Val(Button2.Location.X) + Val(Button2.Size.Width)) - Val(Button1.Location.X)) / 5
                g.FillRectangle(nonpen, x - 3, y - 3, w + 6, h + 6)
                If n <= nowexaminfo.eachnum(cha) Then
                    g.FillRectangle(haventpen, x, y, w, h)
                    g.DrawRectangle(olddoingpen, x, y, w, h)
                    If n > 9 Then
                        x -= 0.11 * w
                    End If
                    g.DrawString(n.ToString, font, Brushes.Black, x + 0.327 * w, y + 0.327 * h)
                End If
            Next
        Next
    End Sub '显示题目是否已经做过的部分初始化
    Sub donereminder(ByRef needti As Integer)
        Dim g As Graphics = Me.CreateGraphics
        Dim havepen As New SolidBrush(Color.MediumSpringGreen) '已做题目
        Dim font As New Font("幼圆", 15)
        Dim x, y, i, j, h, w As Single
        If needti > 5 Then
            i = needti - 6
            j = 1
        Else
            i = needti - 1
            j = 0
        End If
        h = ((Val(Button2.Location.X) + Val(Button2.Size.Width)) - Val(Button1.Location.X)) / 6
        w = h
        x = Val(Button1.Location.X) + ((Val(Button2.Location.X) + Val(Button2.Size.Width)) - Val(Button1.Location.X)) / 60 + i * ((Val(Button2.Location.X) + Val(Button2.Size.Width)) - Val(Button1.Location.X)) / 5
        y = Val(Label2.Location.Y) + ((Val(Button2.Location.X) + Val(Button2.Size.Width)) - Val(Button1.Location.X)) / 60 + j * ((Val(Button2.Location.X) + Val(Button2.Size.Width)) - Val(Button1.Location.X)) / 5
        g.FillRectangle(havepen, x, y, w, h)
        If needti > 9 Then
            x -= 0.11 * w
        End If
        g.DrawString(needti.ToString, Font, Brushes.Black, x + 0.327 * w, y + 0.327 * h)
    End Sub '用于将用户已做题目进行标记
    Sub doingreminder()
        Dim g As Graphics = Me.CreateGraphics
        Dim doingpen As New Pen(Brushes.MediumSlateBlue, 5)
        Dim olddoingpen As New Pen(Brushes.AntiqueWhite, 5)
        Dim i, j, x, y, w, h As Single
        If oldti <> 0 Then
            If oldti > 5 Then
                i = oldti - 6
                j = 1
            Else
                i = oldti - 1
                j = 0
            End If
            h = ((Val(Button2.Location.X) + Val(Button2.Size.Width)) - Val(Button1.Location.X)) / 6
            w = h
            x = Val(Button1.Location.X) + ((Val(Button2.Location.X) + Val(Button2.Size.Width)) - Val(Button1.Location.X)) / 60 + i * ((Val(Button2.Location.X) + Val(Button2.Size.Width)) - Val(Button1.Location.X)) / 5
            y = Val(Label2.Location.Y) + ((Val(Button2.Location.X) + Val(Button2.Size.Width)) - Val(Button1.Location.X)) / 60 + j * ((Val(Button2.Location.X) + Val(Button2.Size.Width)) - Val(Button1.Location.X)) / 5
            g.DrawRectangle(olddoingpen, x, y, w, h)
        End If
        If ti > 5 Then
            i = ti - 6
            j = 1
        Else
            i = ti - 1
            j = 0
        End If
        h = ((Val(Button2.Location.X) + Val(Button2.Size.Width)) - Val(Button1.Location.X)) / 6
        w = h
        x = Val(Button1.Location.X) + ((Val(Button2.Location.X) + Val(Button2.Size.Width)) - Val(Button1.Location.X)) / 60 + i * ((Val(Button2.Location.X) + Val(Button2.Size.Width)) - Val(Button1.Location.X)) / 5
        y = Val(Label2.Location.Y) + ((Val(Button2.Location.X) + Val(Button2.Size.Width)) - Val(Button1.Location.X)) / 60 + j * ((Val(Button2.Location.X) + Val(Button2.Size.Width)) - Val(Button1.Location.X)) / 5
        g.DrawRectangle(doingpen, x, y, w, h)
    End Sub '用于圈出用户正在做的题目并将上一个圈抹掉
    Sub reappear()
        Dim temp2statistic As tempexamstatistics, i As Integer
        '题目不变是不处理-------------------------------------
        If oldcha = cha And oldti = ti Then
            Exit Sub
        End If
        '未改变章节时处理方法----------------------------------
        If oldcha = cha Then '重现选项
            For i = 0 To UBound(statistics)
                temp2statistic = statistics(i)
                If temp2statistic.ti = ti Then
                    '重现选项
                    Select Case temp2statistic.ans
                        Case "A"
                            ifinitialize = True '--------------
                            A.Checked = True
                            ifinitialize = False
                        Case "B"
                            ifinitialize = True '--------------
                            B.Checked = True
                            ifinitialize = False
                        Case "C"
                            ifinitialize = True '--------------
                            C.Checked = True
                            ifinitialize = False
                        Case "D"
                            ifinitialize = True '--------------
                            D.Checked = True
                            ifinitialize = False
                        Case "E"
                            ifinitialize = True '--------------
                            OE.Checked = True
                            ifinitialize = False
                        Case ""
                            ifinitialize = True '--------------
                            A.Checked = False
                            ifinitialize = True '--------------
                            B.Checked = False
                            ifinitialize = True '--------------
                            C.Checked = False
                            ifinitialize = True '--------------
                            D.Checked = False
                            ifinitialize = True '--------------
                            OE.Checked = False
                            nows = i
                            ifinitialize = False
                            Exit Sub
                    End Select
                End If
            Next

        End If
        '章节改变------------------------------------------------
        '选项重现-------------------
        For i = 0 To UBound(statistics)
            temp2statistic = statistics(i)
            If temp2statistic.ti = ti And temp2statistic.chap = cha Then
                '重现选项
                Select Case temp2statistic.ans
                    Case "A"
                        ifinitialize = True '--------------
                        A.Checked = True
                        ifinitialize = False
                    Case "B"
                        ifinitialize = True '--------------
                        B.Checked = True
                        ifinitialize = False
                    Case "C"
                        ifinitialize = True '--------------
                        C.Checked = True
                        ifinitialize = False
                    Case "D"
                        ifinitialize = True '--------------
                        D.Checked = True
                        ifinitialize = False
                    Case "E"
                        ifinitialize = True '--------------
                        OE.Checked = True
                        ifinitialize = False
                    Case ""
                        ifinitialize = True '--------------
                        A.Checked = False
                        ifinitialize = True '--------------
                        B.Checked = False
                        ifinitialize = True '--------------
                        C.Checked = False
                        ifinitialize = True '--------------
                        D.Checked = False
                        ifinitialize = True '--------------
                        OE.Checked = False
                        ifinitialize = False
                        nows = i
                End Select
            End If
        Next
        '图形覆盖-------------------
        doornotremindercover()
        '图形重现-------------------
        For Each temp2statistic In statistics
            If temp2statistic.chap = cha And temp2statistic.ans <> "" Then
                donereminder(temp2statistic.ti)
            End If
        Next
        ifinitialize = False  '--------------
    End Sub '用于重现本次已答题目（包括选项重现，图片重现）=================options
    Sub chaandtiprocessor()
        If chapterselectednno = -1 And cha <> TextBox1.Text Then
            If MsgBox("你确定要离开本章吗？", MsgBoxStyle.Question + MsgBoxStyle.OkCancel) = MsgBoxResult.Cancel Then
                cha = oldcha
                ti = oldti
            End If
        End If
        If Val(TextBox2.Text) < 1 Then
            ti = 1
        End If
        If cha > nowexaminfo.chapter Then
            MsgBox("已经最后一章了!", MsgBoxStyle.Exclamation + MsgBoxStyle.OkOnly)
            cha = oldcha
            ti = oldti
        End If
        If Val(TextBox2.Text) > nowexaminfo.eachnum(cha) Then '当题号超过本章题目时
            cha += 1
            ti = 1
        End If
        If Val(TextBox1.Text) < 1 Then
            cha = 1
            MsgBox("已经到底了！")
        End If
        If cha > nowexaminfo.chapter Then
            MsgBox("已经最后一章了!", MsgBoxStyle.Exclamation + MsgBoxStyle.OkOnly)
            cha = oldcha
            ti = oldti
        End If
        If chapterselectednno = -1 And cha <> oldcha Then
            If MsgBox("你确定要离开本章吗？", MsgBoxStyle.Question + MsgBoxStyle.OkCancel) = MsgBoxResult.Cancel Then
                cha = oldcha
                ti = oldti
            End If
        End If
        TextBox1.Text = cha
        TextBox2.Text = ti
        '处理cha和ti-------------------------------------------
        Dim i As Integer '防止重复记录
        If cha = oldcha And ti = oldti Then '数据未改变时跳过下面步骤
            Exit Sub
        End If
        printexam(cha, ti)
        For i = 0 To UBound(statistics) '防止重复记录
            If tempexam.chapter = statistics(i).chap And tempexam.NO = statistics(i).ti Then
                nows = i
                Exit Sub
            End If
        Next
        '判断不重复后加大统计变量
        ReDim Preserve statistics(Val(UBound(statistics)) + 1)
        nows = UBound(statistics)
        With statistics(nows)
            .key = tempexam.key
            .chap = cha
            .ti = ti
        End With
        ifinitialize = True '--------------
        A.Checked = False
        ifinitialize = True '--------------
        B.Checked = False
        ifinitialize = True '--------------
        C.Checked = False
        ifinitialize = True '--------------
        D.Checked = False
        ifinitialize = True '--------------
        OE.Checked = False
        ifinitialize = False
    End Sub '用于确认cha和ti应显示的值，并输出
    Sub printexam(ByVal chap As Integer, ti As Integer) '只负责打开相应题目
        Label2.Visible = False
        A.Visible = False
        LabelA.Visible = False
        Label3.Visible = False
        B.Visible = False
        LabelB.Visible = False
        Label4.Visible = False
        C.Visible = False
        LabelC.Visible = False
        Label5.Visible = False
        D.Visible = False
        LabelD.Visible = False
        Label6.Visible = False
        OE.Visible = False
        LabelE.Visible = False

        Dim fileno, i, position As Integer, chinesenum As String
        chinesenum = "一二三四五六七八"
        position = 0
        '获取题目位置
        For i = 1 To chap - 1
            position += nowexaminfo.eachnum(i)
        Next
        position += ti
        'position = 1 '========================================================测试使用
        fileno = FreeFile()
        FileOpen(fileno, "exam.txt", OpenMode.Random, , , 1024) '-----------------------------------open
        FileGet(fileno, tempexam, position + 1)
        FileClose(fileno) '---------------------------------------------------------------------------close
        '显示
        Label9.Text = "第" & Mid(chinesenum, chap, 1) & "章" & Space(2) & nowexaminfo.name(chap) '标题
        Label1.Text = tempexam.stem
        If tempexam.A <> "" Then
            Label2.Text = tempexam.A
            Label2.Visible = True
            A.Visible = True
            LabelA.Visible = True
        End If
        If tempexam.B <> "" Then
            Label3.Text = tempexam.B
            Label3.Visible = True
            B.Visible = True
            LabelB.Visible = True
        End If
        If tempexam.C <> "" Then
            Label4.Text = tempexam.C
            Label4.Visible = True
            C.Visible = True
            LabelC.Visible = True
        End If
        If tempexam.D <> "" Then
            Label5.Text = tempexam.D
            Label5.Visible = True
            D.Visible = True
            LabelD.Visible = True
        End If
        If tempexam.E <> "" Then
            Label6.Text = tempexam.E
            Label6.Visible = True
            OE.Visible = True
            LabelE.Visible = True
        End If '打开题目，获取本题信息=========待拆卸

    End Sub 'd‘打开题目获取本题信息

    Private Sub 答题_KeyDown(sender As Object, e As KeyEventArgs) Handles Me.KeyDown

        If e.KeyCode = Keys.A Then
            A.Checked = True
            statistics(nows).ans = "A"
        End If
        If e.KeyCode = Keys.B Then
            B.Checked = True
            statistics(nows).ans = "B"
        End If
        If e.KeyCode = Keys.C Then
            C.Checked = True
            statistics(nows).ans = "C"

        End If
        If e.KeyCode = Keys.D Then
            D.Checked = True
            statistics(nows).ans = "D"
        End If
        If e.KeyCode = Keys.E Then
            OE.Checked = True
            statistics(nows).ans = "E"
        End If
        If e.KeyCode = Keys.Enter Then
            TextBox2.Text = Val(TextBox2.Text) + 1
            ti += 1
        End If
    End Sub '键盘答题

    Private Sub 答题_Load(sender As Object, e As EventArgs) Handles MyBase.Load

        ReDim statistics(0)
        nows = 0
        cha = chapterselected
        If chapterselectednno = -1 Then
            ti = 1
        Else
            ti = chapterselectednno.ToString
        End If
        printexam(cha, ti)
        With statistics(nows)
            .key = tempexam.key
            .chap = cha
            .ti = ti
        End With
        TextBox1.Text = cha.ToString
        TextBox2.Text = ti.ToString
        Timer1.Enabled = True
        Timer2.Enabled = True
        starttime = Now
        KeyPreview = True
    End Sub '加载，初始化

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        If MsgBox("你确定要提交吗？", MsgBoxStyle.Question + MsgBoxStyle.OkCancel) = MsgBoxResult.Ok Then
            Label8.Visible = True
            Dim fileno, i, j As Integer, tempgetstatistic As tempexamstatistics
            '对比查找所需记录位置
            For i = 1 To nowexaminfo.chapter
                For j = 1 To nowexaminfo.eachnum(i)
                    For Each tempgetstatistic In statistics
                        If tempgetstatistic.chap = i And tempgetstatistic.ti = j Then '找到位置并记录
                            nowscore.exam(i, j).alldone += 1
                            If UCase(tempgetstatistic.key) <> UCase(tempgetstatistic.ans) Then
                                nowscore.exam(i, j).falsedone += 1
                            End If
                        End If
                    Next
                Next
            Next
            fileno = FreeFile()
            FileOpen(fileno, "score.txt", OpenMode.Random, , , 1024) '-----------------------------------open
            FilePut(fileno, nowscore, nowuser.NO + 1)
            FileClose(fileno) '--------------------------------------------------------------------------close
            Label8.Visible = False
            '传递本次答题变量，为统计准备
            For i = 1 To nowexaminfo.chapter
                For j = 1 To nowexaminfo.eachnum(i)
                    nowscore.exam(i, j).alldone = 0
                    nowscore.exam(i, j).falsedone = 0
                    For Each tempgetstatistic In statistics
                        If tempgetstatistic.chap = i And tempgetstatistic.ti = j Then '找到位置并记录
                            nowscore.exam(i, j).alldone += 1
                            If UCase(tempgetstatistic.key) <> UCase(tempgetstatistic.ans) Then
                                nowscore.exam(i, j).falsedone += 1
                            End If
                        End If
                    Next
                Next
            Next
            MsgBox("提交完成！")
            统计_用户_.Show()
            Me.Close()
        Else
            Exit Sub
        End If
    End Sub '提交================

    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click
        oldcha = Val(TextBox1.Text)
        oldti = Val(TextBox2.Text)
        TextBox1.Text = Val(TextBox1.Text) + 1
        cha += 1
        chaandtiprocessor()
        reappear()
        doingreminder()
    End Sub '章+1

    Private Sub Button4_Click(sender As Object, e As EventArgs) Handles Button4.Click, Button1.Click
        oldcha = Val(TextBox1.Text)
        oldti = Val(TextBox2.Text)
        TextBox2.Text = Val(TextBox2.Text) + 1
        ti += 1
        chaandtiprocessor()
        reappear()
        doingreminder()
    End Sub '题+1

    Private Sub Button5_Click(sender As Object, e As EventArgs) Handles Button5.Click
        oldcha = Val(TextBox1.Text)
        oldti = Val(TextBox2.Text)
        TextBox1.Text = Val(TextBox1.Text) - 1
        cha -= 1
        chaandtiprocessor()
        reappear()
        doingreminder()
    End Sub '章-1

    Private Sub Button6_Click(sender As Object, e As EventArgs) Handles Button6.Click
        oldcha = Val(TextBox1.Text)
        oldti = Val(TextBox2.Text)
        TextBox2.Text = Val(TextBox2.Text) - 1
        ti -= 1
        chaandtiprocessor()
        reappear()
        doingreminder()
    End Sub '题-1

    Private Sub CheckedChanged(sender As Object, e As EventArgs) Handles B.CheckedChanged, A.CheckedChanged, C.CheckedChanged, D.CheckedChanged, OE.CheckedChanged
        If ifinitialize = True Then
            ifinitialize = False
            Exit Sub
        End If
        If A.Checked = False And B.Checked = False And C.Checked = False And D.Checked = False And OE.Checked = False Then
            Exit Sub
        End If
        donereminder(ti) '将该题标记为已做
        doingreminder()
        If A.Checked = True Then
            statistics(nows).ans = "A"
        End If
        If B.Checked = True Then
            statistics(nows).ans = "B"
        End If
        If C.Checked = True Then
            statistics(nows).ans = "C"
        End If
        If D.Checked = True Then
            statistics(nows).ans = "D"
        End If
        If OE.Checked = True Then
            statistics(nows).ans = "E"
        End If
        Dim fileno, position As Integer
        fileno = FreeFile()
        tempexam.summary(0) += 1
        If UCase(statistics(nows).ans) <> UCase(tempexam.key) Then
            tempexam.summary(1) += 1
        End If
        position = 0
        For i = 1 To tempexam.chapter - 1
            position += nowexaminfo.eachnum(i)
        Next
        position += tempexam.NO
        FileOpen(fileno, "exam.txt", OpenMode.Random, , , 1024) '----------------------open
        FilePut(fileno, tempexam, position + 1)
        FileClose(fileno) '-------------------------------------------------------------close
        Debug.Print(statistics(nows).ans)
    End Sub '选择选项

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick '初始画图
        doornotremindercover()
        doingreminder()
        Timer1.Enabled = False
    End Sub '初始画图

    Private Sub Timer2_Tick(sender As Object, e As EventArgs) Handles Timer2.Tick
        Dim diff As String
        Dim m, s As Integer
        s = DateDiff(DateInterval.Second, starttime, Now)
        m = DateDiff(DateInterval.Minute, starttime, Now)
        s = s - 60 * (s \ 60)
        m = m - 60 * (m \ 60)
        diff = DateDiff(DateInterval.Hour, starttime, Now) & ":" & m.ToString & ":" & s.ToString
        LabelTIME.Text = "你已经练习了" & diff
    End Sub '显示练习时间
End Class