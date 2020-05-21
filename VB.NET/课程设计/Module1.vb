Module Module1
    Public Structure user
        Dim NO As Integer '编号
        Dim name As String '用户名
        Dim password As String '密码
        Dim reservation1 As Integer
        Dim reservation2 As String
        Dim reservation3 As String
    End Structure
    Public Structure userinfo
        Dim num As Integer '用户个数
        Dim reservation1 As Integer
        Dim reservation2 As String
        Dim reservation3 As String
    End Structure
    Public Structure scoreinfo
        Dim reservation1 As Integer
        Dim reservation2 As String
        Dim reservation3 As String
    End Structure
    Public Structure alldoneorefalsedone
        Dim alldone As Integer
        Dim falsedone As Integer
    End Structure
    Public Structure score
        Dim NO As Integer '编号
        Dim exam(,) As alldoneorefalsedone '（章节，题目，)
        Dim reservation1 As Integer
        Dim reservation2 As String
    End Structure
    Public Structure examinfo
        Dim sum As Integer '总共题目数
        Dim chapter As Integer '章数
        Dim eachnum() As Integer '每章题目数
        Dim name() As String '每章名称
        Dim reservation2 As String
    End Structure
    Public Structure exam
        Dim chapter As Integer '所属章节
        Dim NO As Integer '章内编号
        Dim stem As String
        Dim A As String
        Dim B As String
        Dim C As String
        Dim D As String
        Dim E As String
        Dim key As String
        Dim summary() As Integer '0是次数，1是错误数
        Dim reservation1 As Integer
        Dim reservation2 As String
    End Structure
    Friend nowuser As user, nowscore As score, nowexaminfo As examinfo, chapterselected As Integer = 1, chapterselectednno As Integer = 1
End Module
