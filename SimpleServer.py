import os
from flask import Flask,render_template,jsonify,make_response,abort,request
import peewee
import json

# 初期設定
app = Flask(__name__)

# SQLiteDBの生成
if not os.path.exists('/tmp'):
    os.mkdir('/tmp')
db= peewee.SqliteDatabase("/tmp/data.db")

################################################################################
# データモデルクラス
class DataModel(peewee.Model):
    now = peewee.TextField()
    val1 = peewee.TextField()
    val2= peewee.IntegerField()

    class Meta:
        database = db
################################################################################

# テーブルの作成
db.create_tables([DataModel])

# 登録API
@app.route('/add', methods=['POST'])
def addData():
    data = json.loads(request.data.decode('utf-8'))
    print(data)
    v = DataModel(now=data["time"],
                val1=data["val1"],
                val2=data["val2"])
    v.save()
    return "{ok}"

@app.route('/')
def index():
    data=DataModel.select()
    return render_template("index.html",data=data)


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=3000)
