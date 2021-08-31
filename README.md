* はじめに

 IoTデバイスと連携して、センサーからデータ受信するWebサービスのサンプルです。

# ソースのチェックアウト
```
git clone https://github.com/tt-hasegawa/IoTSample.git
```

# Webサーバの起動
Serverフォルダにてコマンドプロンプト／シェルを開く

以下のコマンドを実行して関連ライブラリをインストールする
```
pip install -r requirements.txt
```
以下のコマンドを実行し、Webサーバを起動する。
```
python SimpleServer.py
``` 

```
 * Running on http://0.0.0.0:3000/ (Press CTRL+C to quit)
```
と表示されたら、サーバ起動OK。


# テスト用クライアントの実行

上記Webサーバを起動した状態で次を実行

clientフォルダにてコマンドプロンプトを開く

以下のコマンドを実行
```
python client.py
``` 

http://localhost:3000 を開いて、データが増えていることを確認する。

# IoTデバイスからの実行

上記Webサーバを起動した状態で次を実行

ArduinoIDEにて、clientフォルダのclient.cをコンパイルしてデバイスに書込み

（WiFIパスワード等は編集しておく）

http://localhost:3000 を開いて、データが増えていることを確認する。


