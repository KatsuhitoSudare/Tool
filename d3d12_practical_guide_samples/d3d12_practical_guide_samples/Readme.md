# サンプルプログラムについて

## 動作確認環境について
　サンプルプログラムは以下の環境で動作確認を行っています。  

* Windows 10 Home 64bit 21H1 19043.110
* Windows 10 SDK 10.0.20161.0
* Visual Studio Community 2019 Version 16.10.3 
* NVIDIA GeForce RTX 2070  
* NVIDIA Graphics Driver 466.11  

　11章のメッシュシェーダのプログラムを動作させるためには，DirectX 12 Ultimateに対応したグラフィックスカードとグラフィックスドライバーが必要になりますので，ご注意ください。  
　また，本書では外部ライブラリとして，assimp と DirectXTK を使用しています。こちらは本書のサンプルに付属せず，各自でVisual Studio起動後にNuGetパッケージをインターネット経由でダウンロードして頂く形になっております。そのため，本書のサンプルプログラムの動作確認にはインターネット接続環境が必要になります。NuGetパッケージのダウンロード方法についてですが，サンプルプログラムのソリューションファイルをVisual Studioで開き，ソリューションエクスプローラー上で，ソリューションを右クリックし，NuGetパッケージの復元を選択して頂くことで，必要なファイルがダウンロードされます。  

## フォルダ構成について

　本書のサンプルプログラムのフォルダ構成は次のようになっています。  

┣ Chapter2フォルダ
┃   ┣ 2.1フォルダ
┃   ┣ 2.2フォルダ
┃   ┣ 2.3フォルダ
┃   ┗ 2.4フォルダ
┣ Chapter3フォルダ
┃   ┣ 3.1フォルダ
┃   ┣ 3.6フォルダ
┃   ┣ 3.8フォルダ
┃   ┗ 3.9フォルダ
┣ Chapter4フォルダ
┃   ┣ 4.2フォルダ
┃   ┣ 4.3フォルダs
┃   ┗ 4.4フォルダ
┣ Chapter5フォルダ
┃   ┣ 5.1フォルダ
┃   ┗ 5.2フォルダ
┣ Chapter6フォルダ
┃   ┣ Bumpフォルダ
┃   ┣ Lamberフォルダ
┃   ┗ Phongフォルダ
┣ Chapter8フォルダ
┃   ┣ CookTorranceフォルダ
┃   ┣ GGXフォルダ
┃   ┣ NormalizedLambertフォルダ
┃   ┗ NormalizedPhongフォルダ
┣ Chapter9フォルダ
┃   ┗　Tonemap
┣ Chapter10フォルダ
┃   ┣ DirectionalLightフォルダ
┃   ┣ ImageBasedLightフォルダ
┃   ┣ PhotometricLightフォルダ
┃   ┣ PointLightフォルダ
┃   ┗ SpotLightフォルダ
┣ Chapter11フォルダ
┃   ┣ Meshletフォルダ
┃   ┗ SimplePolygonフォルダ
┣ Appendixフォルダ
┃   ┗ CPUDebug
┣ Figureフォルダ
┣ Readme.md
┗ LICENSE

　本書の各章に対応するようにフォルダ階層を分けております。各Chapterのフォルダには完成済みのソースコード一式が入っております。ただし，Chapter9, Chapter10, Chapter11にはHDRテクスチャが付属しませんので，動作させるためには，各自でテクスチャを用意していただき，サンプルプログラム上のファイル名を用意して頂いたテクスチャファイルパスに書き換えて頂く必要があるのでご注意ください。  
　Figureフォルダには本書の図データが格納されています。  
　本書のサンプルプログラムはMITライセンスと致します。詳細はLICENSEファイルをご参照ください。  
