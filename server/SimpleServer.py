import os
from flask import Flask,render_template,request
import peewee
import json

# SQLiteDBの生成
db = peewee.SqliteDatabase("data.db")

################################################################################
# データモデルクラス
class SampleDataModel(peewee.Model):
    now = peewee.TextField()
    val1 = peewee.TextField(null=True)
    val2= peewee.IntegerField(null=True)

    class Meta:
        database = db
################################################################################

# テーブルの作成
db.create_tables([SampleDataModel])

# Webサーバ初期設定
app = Flask(__name__)

# 登録API
@app.route('/add', methods=['POST'])
def addData():
    # JSONを受け取る。
    data = request.json
    # DBモデルに変換して保存。
    v = SampleDataModel(now=data["now"], val1=data["val1"], val2=data["val2"])
    v.save()
    return "{ok}"

# 画面表示部分
@app.route('/')
def index():
    # データを取得してhtmlに描画する
    data=SampleDataModel.select()
    return render_template("index.html",data=data)

# Webサーバ起動
if __name__ == '__main__':
    app.run(host='0.0.0.0')
