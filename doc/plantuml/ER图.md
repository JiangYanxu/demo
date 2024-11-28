# ER图
又称实体-关系图，是一种用来描述实体和实体之间关系的图表。
## 基本元素
* Entity 实体，一个对象，表示数据库要存储的信息；矩形表示
  * 弱实体；双矩形表示（回）
    判断实体是否是弱实体：看该实体是否完全依赖于另一个实体来唯一标识。
* Attribute 属性，描述**实体**或**关系**的特征；椭圆形表示
  * 唯一属性，下划线表示
  * 非唯一属性
  * 多值属性，双椭圆表示
    理论上应该是个一对多的关系，但没必要。
  * 派生属性，从其他属性派生而来，用虚线椭圆表示
    从其他属性推导来的，比如年龄可由生日推导而来
* Relationship 关系，描述实体之间的联系；菱形表示
  * 一对一；一对多；多对多；1代表一，N代表多
  * Identifying 标识关系（识别关系） 用以标识弱实体与其依赖的强实体之间的关联。
    强实体的主键作为弱实体的主键的一部分，从而唯一标识弱实体的实例。
  * 用实线标识关系与实体的关联，用粗线或双线标识强关联（强制参与）。
## 笔记
### 实体与属性
水平布局、主键、派生属性、多值属性、组合属性（DB中多列）
```plantuml
@startchen
' 水平布局
' left to right direction
entity 导演 {
    身份证号 : INTEGER <<key>>
    年龄 : INTEGER <<derived>>
    作品id : INTEGER <<multi>>
    出生日期 : DATE
    死亡
    名字 {
        姓
        名
    }
}
@endchen
```
### 关系
关系属性、关系数量、实体别名、属性别名、强制关联
```plantuml
@startchen
entity "客户" as customer{
    "客户id : INTEGER" as customer_id <<key>>
    姓名 : STRING
}
entity "电影" as movie {
    电影id : INTEGER <<key>>
    名称 : STRING
    导演id : INTEGER <<foreign>>
}
relationship "租用给" as rent_to {
    日期 : DATE
}
' 也可以是个范围
' customer -(1,N)- rent_to
' movie =(0,1)= rent_to
customer -1- rent_to
movie =N= rent_to
@endchen
```
### 标识关系 Identifying
弱实体
孩子的主键由父母的身份证+孩子的姓名标识。
```plantuml
@startchen
entity "父母" as parent {
  身份证号 <<key>>
}
' 孩子没身份证号之前
entity "孩子" as child <<weak>> {
  名字 <<key>>
}
relationship "生于" as parent_of <<identifying>> {
}
parent -1- parent_of
child =N= parent_of
@endchen
```
### 还有继承？
符号来自集合论.... 用上时再看吧。


