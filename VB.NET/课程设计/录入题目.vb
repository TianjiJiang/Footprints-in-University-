Public Class 录入题目
    Dim siteNOW As String '记录正在读取的项目
    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        If Trim(TextBox1.Text) = "" Or Trim(TextBox2.Text) = "" Or Trim(TextBox3.Text) = "" Or Trim(TextBox4.Text) = "" Or Trim(TextBox7.Text) = "" Or Trim(TextBox8.Text) = "" Then
            MsgBox("请输入题目完整信息")
            Label9.Visible = False
            Exit Sub
        End If
        Dim exam As exam, examinfo As examinfo '-----------------------------该题目部分
        ReDim exam.summary(1) '题目基本信息
        With exam
            .stem = TextBox1.Text
            .A = TextBox2.Text
            .B = TextBox3.Text
            .C = TextBox4.Text
            .D = TextBox5.Text
            .E = TextBox6.Text
            .chapter = Val(TextBox8.Text)
            .key = TextBox7.Text
            .summary(0) = 0
            .summary(1) = 0
            .reservation1 = 0
            .reservation2 = ""
        End With
        Dim fileno1 As Integer
        fileno1 = FreeFile()
        FileOpen(fileno1, "exam.txt", OpenMode.Random, , , 1024) '----------------open
        FileGet(fileno1, examinfo, 1)
        If exam.chapter > examinfo.chapter + 1 Then
            MsgBox("请输入连续章节题目")
            Exit Sub
        End If
        examinfo.sum += 1 '总题目数加一
        If exam.chapter > examinfo.chapter Then '判断是否为新章节
            examinfo.chapter += 1
            ReDim Preserve examinfo.name(UBound(examinfo.name) + 1) '增加新章节
            examinfo.name(UBound(examinfo.name)) = InputBox("请输入新章节的名字")
            ReDim Preserve examinfo.eachnum(UBound(examinfo.eachnum) + 1) '增加新章节题目数量的统计
            examinfo.eachnum(UBound(examinfo.eachnum)) = 1 '题目数量从一开始
            exam.NO = 1
            FilePut(fileno1, examinfo, 1)
            FilePut(fileno1, exam, examinfo.sum + 1)
        ElseIf exam.chapter < examinfo.chapter Then
            Dim rotat As Integer, tempexam As exam, times As Integer
            exam.NO = examinfo.eachnum(exam.chapter) + 1
            rotat = 0
            For rotat = exam.chapter + 1 To examinfo.chapter
                times += examinfo.eachnum(rotat)
            Next
            For rotat = 1 To times '将后面的题向后挪
                FileGet(fileno1, tempexam, examinfo.sum + 1 - rotat)
                FilePut(fileno1, tempexam, examinfo.sum + 2 - rotat)

            Next
            FilePut(fileno1, exam, examinfo.sum + 2 - rotat)
            examinfo.eachnum(exam.chapter) += 1
            FilePut(fileno1, examinfo, 1)
        Else
            exam.NO = examinfo.eachnum(exam.chapter) + 1
            examinfo.eachnum(exam.chapter) += 1
            FilePut(fileno1, examinfo, 1)
            FilePut(fileno1, exam, examinfo.sum + 1)
        End If

        FileClose(fileno1) '---------------------------------------------------------close
        Label9.Visible = True
        TextBox1.Text = ""
        TextBox2.Text = ""
        TextBox3.Text = ""
        TextBox4.Text = ""
        TextBox5.Text = ""
        TextBox6.Text = ""
        TextBox7.Text = ""

        '===============================================改题目部分
        ''-------------------------------------------------------------------------------改分数部分

        ''==============================================================================改分数部分
        Label10.Text = "本章已经录入" & examinfo.eachnum(Val(TextBox8.Text)) & "题"
        'Dim transstr As String

        'Dim a, b As Integer '记录位置
        'fileno1 = FreeFile()
        'FileOpen(fileno1, "第二章.txt", OpenMode.Input) '-------------------------------------------------OPEN
        'Do While Not EOF(fileno1)
        '    Input(fileno1, transstr)
        '    If Not (InStr(transstr, "、") <> -1 And InStr(transstr, "、") < 4) And Not (InStr(transstr, "（") <> -1 And InStr(transstr, "）") <> -1) And Not (InStr(transstr, "A.") <> -1) And Not (InStr(transstr, "B.") <> -1) And Not (InStr(transstr, "C.") <> -1) And Not (InStr(transstr, "D.") <> -1) And Not (InStr(transstr, "E.") <> -1) Then
        '        Select Case UCase(siteNOW)
        '            Case "S"
        '                TextBox1.Text += transstr
        '            Case "A"
        '                TextBox2.Text += transstr
        '            Case "B"
        '                TextBox3.Text += transstr
        '            Case "C"
        '                TextBox4.Text += transstr
        '            Case "D"
        '                TextBox5.Text += transstr
        '            Case "E"
        '                TextBox6.Text += transstr
        '        End Select
        '        Continue Do
        '    End If
        '    If InStr(transstr, "、") <> -1 And InStr(transstr, "、") < 4 Then '识别题干，防止题干中顿号干扰
        '        siteNOW = "S"
        '        If InStr(transstr, "（") = -1 Then
        '            TextBox1.Text += Mid(transstr, InStr(transstr, "、") - 1, Len(transstr))
        '        Else
        '            TextBox1.Text += Mid(a, InStr(transstr, "、") + +1, InStr(transstr, "（") - InStr(transstr, "、") - 1)
        '        End If
        '    End If
        '    If InStr(transstr, "（") <> -1 And InStr(transstr, "）") <> -1 Then '识别答案,并提取
        '        TextBox7.Text = Trim(Mid(transstr, InStr(transstr, "（") + 1, InStr(transstr, "）") - 1))
        '    End If
        '    If InStr(transstr, "A.") <> -1 Then '识别选项A，为其它选项做准备
        '        siteNOW = "a"
        '        If InStr(transstr, "B.") <> -1 Then '判断该行是否有B
        '            b = InStr(transstr, "B.")
        '            a = InStr(transstr, "A.")
        '            TextBox2.Text = Trim(Mid(transstr, a + 1, a - b - 2))
        '            transstr = Mid(transstr, a + 1, Len(transstr))
        '        Else
        '            TextBox2.Text = Trim(Mid(transstr, a + 1, Len(transstr)))
        '        End If
        '    End If
        '    If InStr(transstr, "B.") <> -1 Then '识别选项B，为其它选项做准备
        '        siteNOW = "B"
        '        If InStr(transstr, "C.") <> -1 Then '判断该行是否有C
        '            a = InStr(transstr, "B.")
        '            b = InStr(transstr, "C.")
        '            TextBox3.Text = Trim(Mid(transstr, a + 1, a - b - 2))
        '            transstr = Mid(transstr, a + 1, Len(transstr))
        '        Else
        '            TextBox3.Text = Trim(Mid(transstr, a + 1, Len(transstr)))
        '        End If
        '    End If
        '    If InStr(transstr, "C.") <> -1 Then '识别选项C，为其它选项做准备
        '        siteNOW = "C"
        '        If InStr(transstr, "D.") <> -1 Then '判断该行是否有D
        '            a = InStr(transstr, "C.")
        '            b = InStr(transstr, "D.")
        '            TextBox4.Text = Trim(Mid(transstr, a + 1, a - b - 2))
        '            transstr = Mid(transstr, a + 1, Len(transstr))
        '        Else
        '            TextBox4.Text = Trim(Mid(transstr, a + 1, Len(transstr)))
        '        End If
        '    End If
        '    If InStr(transstr, "D.") <> -1 Then '识别选项D，为其它选项做准备
        '        siteNOW = "D"
        '        If InStr(transstr, "E.") <> -1 Then '判断该行是否有E
        '            a = InStr(transstr, "D.")
        '            b = InStr(transstr, "E.")
        '            TextBox5.Text = Trim(Mid(transstr, a + 1, a - b - 2))
        '            transstr = Mid(transstr, a + 1, Len(transstr))
        '        Else
        '            TextBox5.Text = Trim(Mid(transstr, a + 1, Len(transstr)))
        '        End If
        '    End If
        '    If InStr(transstr, "B.") <> -1 Then '识别选项E，
        '        siteNOW = "E"
        '        TextBox6.Text = Trim(Mid(transstr, a + 1, Len(transstr)))
        '    End If
        'Loop

    End Sub


    Private Sub 录入题目_Load(sender As Object, e As EventArgs) Handles Me.Load
        'Dim transstr As String
        'Dim FILENO1 As Integer
        'siteNOW = "S"
        'Dim a, b As Integer '记录位置
        'FILENO1 = FreeFile()
        'FileOpen(FILENO1, "第一章.txt", OpenMode.Input) '-------------------------------------------------OPEN
        'Do While Not EOF(FILENO1)
        '    transstr = LineInput(FILENO1)
        '    If Not (InStr(transstr, "、") <> -1 And InStr(transstr, "、") < 4) And Not (InStr(transstr, "（") <> -1 And InStr(transstr, "）") <> -1) And Not (InStr(transstr, "A.") <> -1) And Not (InStr(transstr, "B.") <> -1) And Not (InStr(transstr, "C.") <> -1) And Not (InStr(transstr, "D.") <> -1) And Not (InStr(transstr, "E.") <> -1) Then
        '        Select Case UCase(siteNOW)
        '            Case "S"
        '                TextBox1.Text += transstr
        '            Case "A"
        '                TextBox2.Text += transstr
        '            Case "B"
        '                TextBox3.Text += transstr
        '            Case "C"
        '                TextBox4.Text += transstr
        '            Case "D"
        '                TextBox5.Text += transstr
        '            Case "E"
        '                TextBox6.Text += transstr
        '        End Select
        '        Continue Do
        '    End If
        '    If InStr(transstr, "、") <> -1 And InStr(transstr, "、") < 4 Then '识别题干，防止题干中顿号干扰
        '        siteNOW = "S"
        '        If InStr(transstr, "（") = -1 Then
        '            TextBox1.Text = Mid(transstr, InStr(transstr, "、") - 1, Len(transstr))
        '        Else
        '            TextBox1.Text = Mid(a, InStr(transstr, "、") + 1, InStr(transstr, "（") - InStr(transstr, "、") - 1)
        '            TextBox7.Text = Trim(Mid(transstr, InStr(transstr, "（") + 1, InStr(transstr, "）") - 1))
        '        End If
        '        Continue Do
        '    End If
        '    If InStr(transstr, "（") <> -1 And InStr(transstr, "）") <> -1 Then '识别答案,并提取
        '        TextBox7.Text = Trim(Mid(transstr, InStr(transstr, "（") + 1, InStr(transstr, "）") - 1))
        '    End If
        '    If InStr(transstr, "A.") <> -1 Then '识别选项A，为其它选项做准备
        '        siteNOW = "a"
        '        If InStr(transstr, "B.") <> -1 Then '判断该行是否有B
        '            TextBox2.Text = Trim(Mid(transstr, InStr(transstr, "A.") + 1, InStr(transstr, "A.") - InStr(transstr, "B.") - 2))
        '            transstr = Mid(transstr, a + 1, Len(transstr))
        '        Else
        '            TextBox2.Text = Trim(Mid(transstr, a + 1, Len(transstr)))
        '        End If
        '    End If
        '    If InStr(transstr, "B.") <> -1 Then '识别选项B，为其它选项做准备
        '        siteNOW = "B"
        '        If InStr(transstr, "C.") <> -1 Then '判断该行是否有C
        '            a = InStr(transstr, "B.")
        '            b = InStr(transstr, "C.")
        '            TextBox3.Text = Trim(Mid(transstr, a + 1, a - b - 2))
        '            transstr = Mid(transstr, a + 1, Len(transstr))
        '        Else
        '            TextBox3.Text = Trim(Mid(transstr, a + 1, Len(transstr)))
        '        End If
        '    End If
        '    If InStr(transstr, "C.") <> -1 Then '识别选项C，为其它选项做准备
        '        siteNOW = "C"
        '        If InStr(transstr, "D.") <> -1 Then '判断该行是否有D
        '            a = InStr(transstr, "C.")
        '            b = InStr(transstr, "D.")
        '            TextBox4.Text = Trim(Mid(transstr, a + 1, a - b - 2))
        '            transstr = Mid(transstr, a + 1, Len(transstr))
        '        Else
        '            TextBox4.Text = Trim(Mid(transstr, a + 1, Len(transstr)))
        '        End If
        '    End If
        '    If InStr(transstr, "D.") <> -1 Then '识别选项D，为其它选项做准备
        '        siteNOW = "D"
        '        If InStr(transstr, "E.") <> -1 Then '判断该行是否有E
        '            a = InStr(transstr, "D.")
        '            b = InStr(transstr, "E.")
        '            TextBox5.Text = Trim(Mid(transstr, a + 1, a - b - 2))
        '            transstr = Mid(transstr, a + 1, Len(transstr))
        '        Else
        '            TextBox5.Text = Trim(Mid(transstr, a + 1, Len(transstr)))
        '        End If
        '    End If
        '    If InStr(transstr, "B.") <> -1 Then '识别选项E，
        '        siteNOW = "E"
        '        TextBox6.Text = Trim(Mid(transstr, a + 1, Len(transstr)))
        '    End If
        'Loop
        'FileClose(FILENO1)
    End Sub
End Class