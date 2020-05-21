import pymysql

def insert(db,table:str,data):#data:对应数据，table:对应表
    if table == 'MaT':
        sql = "INSERT INTO MaT(Mno,Mname,Pri) VALUES " + str(data) + ";"
    elif table == 'Me_Re':
        sql = "INSERT INTO Me_Re(Sno,Pno,M_time) VALUES " + str(data) + ";"
    elif table == 'Pre':
        sql = "INSERT INTO Pre(Pno,Mno,num,mom_sum,payornot) VALUES " + str(data) + ";"
    elif table == 'Stu':
        sql = "INSERT INTO Stu(Sno,Sname,Age,collage,indent,MT,mon_unpay,mon_payed,afr) VALUES " + str(data) + ';'
    elif table == 'Stu_info':
        sql = "INSERT INTO Stu_info(Sno,Sname,Age,collage,indent,MT) VALUES " + str(data) + ';'


    else :
        return -1

    try:
        cursor = db.cursor()
        cursor.execute(sql)
        db.commit()
        return 0
    except:
        db.rollback()
        return 1

def select(db,way:str,*data):
    
    if  way == "":
        return 2
    
    elif way == "reg_S_info_n":#no input output all
        sql = '''SELECT Sno,Sname,Age,collage,indent,MT
                 FROM Stu_info;'''

    elif way == "reg_S_info_s_Sno":#single info(Sno) input
        sql = '''SELECT Sno,Sname,Age,collage,indent,MT
                 FROM Stu_info
                 WHERE Sno  = '{0}';'''.format(data[0])
        
    elif way == "reg_S_info_s_Sname":#single info(Sname) input
        sql = '''SELECT Sno,Sname,Age,collage,indent,MT
                 FROM Stu_info
                 WHERE Sname  = '{0}';'''.format(data[0])

    elif way == "reg_S_info_D_info":#double info input
        sql = '''SELECT Sno,Sname,Age,collage,indent,MT
                 FROM Stu_info
                 WHERE Sno = '{0}' AND Sname = '{1}';'''.format(data[0],data[1])

    elif way == "reg_S_reg_n":#no input output all
        sql = '''SELECT Me_Re.Sno,Sname,Pno,M_time
                 FROM Stu_info,Me_Re
                 WHERE Stu_info.Sno = Me_Re.Sno;'''

    elif way == "reg_S_reg_s_Sno":#single info(Sno) input
        sql = '''SELECT Me_Re.Sno,Sname,Pno,M_time
                 FROM Stu_info,Me_Re
                 WHERE Stu_info.Sno = Me_Re.Sno and Stu_info.Sno  = '{0}';'''.format(data[0])
        
    elif way == "reg_S_reg_s_Sname":#single info(Sname) input
        sql = '''SELECT Me_Re.Sno,Sname,Pno,M_time
                 FROM Stu_info,Me_Re
                 WHERE Stu_info.Sno = Me_Re.Sno and Stu_info.Sname  = '{0}';'''.format(data[0])

    elif way == "reg_S_reg_D_info":#double info input
        sql = '''SELECT Me_Re.Sno,Sname,Pno,M_time
                 FROM Stu_info,Me_Re
                 WHERE Stu_info.Sno = Me_Re.Sno and Stu_info.Sno = '{0}' AND Sname = '{1}';'''.format(data[0],data[1])

    elif way == "pri_n":
        sql = '''SELECT Mno,Mname,Pri 
                FROM MaT;'''
    
    elif way == "pri_s_Mno":
        sql = '''SELECT Mno,Mname,Pri 
                FROM MaT
                WHERE Mno = '{}';'''.format(*data)
    
    elif way == "pri_s_Mname":
        sql = '''SELECT Mno,Mname,Pri 
                FROM MaT
                WHERE Mname = '{}';'''.format(*data)
    
    elif way == "pri_D":
        sql = '''SELECT Mno,Mname,Pri 
                FROM MaT
                WHERE Mno = '{0}'AND Mname = '{1}';'''.format(*data)           

    elif way == "pri_SP_n":
        sql = '''SELECT Me_Re.Sno,Me_Re.Pno,MaT.Mname,Pre.mom_sum,Pre.payornot
                FROM Me_Re,MaT,Pre
                WHERE Me_Re.Pno = Pre.Pno AND Pre.Mno = MaT.Mno;'''

    elif way == "pri_SP_s_Sno":
        sql = '''SELECT Me_Re.Sno,Me_Re.Pno,MaT.Mname,Pre.mom_sum,Pre.payornot
                FROM Me_Re,MaT,Pre
                WHERE Me_Re.Pno = Pre.Pno AND Pre.Mno = MaT.Mno AND Me_Re.Sno = '{}';'''.format(*data)

    elif way == "pri_SP_s_Pno":
        sql = '''SELECT Me_Re.Sno,Me_Re.Pno,MaT.Mname,Pre.mom_sum,Pre.payornot
                FROM Me_Re,MaT,Pre
                WHERE Me_Re.Pno = Pre.Pno AND Pre.Mno = MaT.Mno AND Pre.Pno = '{}';'''.format(*data)

    elif way == "pri_SP_D":
        sql = '''SELECT Me_Re.Sno,Me_Re.Pno,MaT.Mname,Pre.mom_sum,Pre.payornot
                FROM Me_Re,MaT,Pre
                WHERE Me_Re.Pno = Pre.Pno AND Pre.Mno = MaT.Mno AND Me_Re.Sno = '{}' AND Pre.Pno = '{}';'''.format(*data)

    elif way == "Dr_Sno_to_Pno":
        sql = '''SELECT Pno
                FROM Me_Re
                WHERE Sno = '{}';'''.format(*data)

    elif way == "Dr_D_Sno_Pno_for_sym_res":
        sql = '''SELECT sym,res
                from Me_Re
                where Sno = '{0}'AND Pno = '{1}';'''.format(*data)

    elif way == "Dr_s_Mname_for_Mno_pri":
        sql = '''SELECT Mno,Pri
                FROM MaT
                where Mname = '{}';'''.format(*data)

    elif way == "Dr_s_Mno_for_Mname_pri":
        sql = '''SELECT Mname,Pri
                FROM MaT
                where Mno = '{}';'''.format(*data)

    elif way == "fin_n":
        sql = '''SELECT Stu.Sno,Stu.Sname,Pno,M_time,mon_unpay,mon_payed,afr
                FROM Stu,Me_Re
                WHERE Stu.Sno = Me_Re.Sno;
                '''   
    
    elif way == "fin_s_Sno":
        sql = '''SELECT Stu.Sno,Stu.Sname,Pno,M_time,mon_unpay,mon_payed,afr
                FROM Stu,Me_Re
                WHERE Stu.Sno = Me_Re.Sno and Stu.Sno = '{}';
                '''.format(*data)
   
    elif way == "fin_s_Sname":
        sql = '''SELECT Stu.Sno,Stu.Sname,Pno,M_time,mon_unpay,mon_payed,afr
                FROM Stu,Me_Re
                WHERE Stu.Sno = Me_Re.Sno and Stu.Sname = '{}';
                '''.format(*data)
    
    elif way == "fin_D":
        sql = '''SELECT Stu.Sno,Stu.Sname,Pno,M_time,mon_unpay,mon_payed,afr
                FROM Stu,Me_Re
                WHERE Stu.Sno = Me_Re.Sno  and Stu.Sname = '{1}'
                and Stu.Sno = '{0}';
                '''.format(*data)

    elif way == "fin_s_Sno_to_fins":
        sql = '''SELECT Sno,Sname,mon_unpay,mon_payed,afr
                FROM Stu_fin
                WHERE Sno = '{}';
                '''.format(*data)

    try:
        cursor = db.cursor()    
        cursor.execute(sql)
        return cursor.fetchall()
    except:
        return -1

def update(db,way:str,*data):
    
    if way == "":
        return 2
    
    elif way == "reg_info_update":
        sql = '''UPDATE Stu_info 
                SET Sname = '{1}',Age = {2},collage = '{3}',indent = '{4}',MT = '{5}'
                WHERE Sno = '{0}';'''.format(*data)
    
    elif way == "MaT":
        sql = '''UPDATE MaT
                SET Mname = '{1}',Pri = '{2}'
                WHERE Mno = '{0}';'''.format(*data)

    elif way == "Pno_to_sym_res":
        sql = '''UPDATE Me_Re
                set sym = '{2}',res = '{3}'
                where Pno = '{0}' and Sno = '{1}';
        '''.format(*data)

    elif way == "pri_onepay":
        sql = '''UPDATE Pre
                set payornot = 1
                where Pno = '{0}';
        '''.format(*data)

    elif way == "Stu_fin":
        sql = '''UPDATE Stu
            set mon_unpay = '{1}',mon_payed = '{2}'
            where Sno = '{0}'
            '''.format(*data)

    try:
        cursor = db.cursor()
        cursor.execute(sql)
        db.commit()
        return 0
    except:
        db.rollback()
        return 1


def who(db):
    cursor = db.cursor()
    sql = "SELECT USER()"
    cursor.execute(sql)
    return cursor.fetchone()


if __name__ == "__main__":
    import pymysql
    db = pymysql.connect("localhost","root","root","hospital")
    cursor = db.cursor()
    res = select(db,"reg_S_info_s_Sno",'0101170216')
    #a = insert(db,'Stu',('0331171226','孙乾坤',19,'本科','普通',0,0,0))
    print(res[0][1:] == ('蒋天济',eval('19'), None, '本科', '普通'))
