# UE5_VoicePeak( & ChatGPT )Sample
![image](https://user-images.githubusercontent.com/8957600/235693868-1c2a984f-80f7-445e-9119-80fc984971fd.png)  
UE5上でVoicePeakを動かすだけのサンプルだったはずが、調子に乗ってChatGPT APIに対応したサンプルです。  
VoicePeak : https://www.ah-soft.com/voice/6nare/  
ChatGPT : https://openai.com/blog/chatgpt

動かしている様子  
https://twitter.com/pafuhana1213/status/1653337540366340098  

# サンプルの使い方・できること
Plugins/VoicePeakUE5 Content 以下にある各EditorUtilityWidgetをどうぞ
- EUW_VoicePeak
  - VoicePeakの各パラメータと指定のテキスト（Script）からボイスデータ(.wav)を生成
  - 生成したボイスデータをプロジェクトにインポート
- EUW_ChatGPT
  - UE5からChatGPTにテキストを送信し、受信したテキスト（回答）を表示
  - ChatGPTとのやり取りを記録した上でテキストを送信 ( Message History )
- EUW_ChatGPT2VoicePeak
  - ChatGPTから受け取ったテキストをVoicePeakにパス（自動化オプション付き）

# サンプルを動かす上で必要なプラグイン
- HttpGPT - GPT Integration (ChatGPT and DALL-E)  
  - https://www.unrealengine.com/marketplace/ja/product/httpgpt-chatgpt-integrated-in-the-engine  
  - ドキュメント：https://github.com/lucoiso/UEHttpGPT/wiki 
- Runtime Audio Importer  
  - https://www.unrealengine.com/marketplace/ja/product/runtime-audio-importer  
  - ドキュメント：https://github.com/gtreshchev/RuntimeAudioImporter/wiki 

どちらも無料で入手可能です。

# ChatGPTを動かす上で必要な設定など
- ChatGPT API Keyは同梱していません。ご自身のものをご使用ください
- EUW_ChatGPT, EUW_ChatGPT2VoicePeak または プロジェクト設定/Plugins/HttpGPT にて APIKeyとユーザ名を入力してください

# 実装する上で参考にした記事
## Voice Peak
- https://atarms.hatenablog.com/entry/2023/03/12/164118
- https://takashiski.hatenablog.com/entry/2023/01/13/235249
- https://atarms.hatenablog.com/entry/2023/03/12/170059
- https://note.com/tori29umai/n/n5f3762bd1231

## ChatGPT
- https://platform.openai.com/docs/api-reference/chat/create
- https://ai-create.net/magazine/2023/03/02/post-10647/
- https://blog.since2020.jp/ai/chatgpt_api_role/

# その他
- VoicePeakの制限により、140文字以上のテキストからボイス生成することはできません。そのため、ChatGPTに「回答は140文字以下で」とか制限をつけることを推奨します
  - 分割した文章毎にボイス生成とか考えましたが、地味に面倒そうなので後回しにしました
- 外部プロセスを呼び出すLatentノードをプラグインに含めてます。UBlueprintAsyncActionBaseでFPlatformProcess::CreateProcを動かしているだけですが参考程度にどうぞ
  - Plugins/VoicePeakUE5/Source/VoicePeakUE5/Public/VoicePeakFunctionLibrary.h
- ChatGPTから回答をもらう際に感情スコアも添えるようにして、それをVoicePeckのオプションに食わせるとかしたい
  - やってみた：https://twitter.com/pafuhana1213/status/1653118678802792449
  - それらのパラメータに応じてキャラのモーションと表情を制御したりしてみたい

# エンジンバージョン
5.1

# 作者
おかず https://twitter.com/pafuhana1213
