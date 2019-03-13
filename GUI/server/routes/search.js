
var express = require('express');
var router = express.Router();
var formidable = require('formidable');
var fs = require("fs");
var process = require('child_process');

var path = require("path");

let sd = require('silly-datetime');


/*
    向前端发送初始化的所有条目
 */

router.post('/initTBodys', function(req, res, next) {
    console.log("开始向前端发送初始化tbodys");

    var raw_file = __dirname + "/" + '..' + "/" + 'Json' +"/" + 'allJson.json';

    console.log(raw_file);
    try{
        var result=JSON.parse(fs.readFileSync(raw_file));
    }catch(err){
        console.log(err)
    }
    console.log(result);
    res.send(result);
    res.end('{"success":"true"}');
});


router.post('/searchInfo', function(req, res, next) {
    console.log("searchInfo 后端启动!");
    console.log(req.body);
    var des_file = __dirname + "/" + '..'+ "/" + 'Json' + "/" + 'searchInfo.json';
    console.log(__dirname);
    var searchInfo={
        sendTime:'',
        confTime:'',
        deadLine:'',
        subject:'',
        location:'',
    }
    try{
        if(req.body.searchInfo.sendTime != '' && req.body.searchInfo.sendTime !=null){
            searchInfo.sendTime = req.body.searchInfo.sendTime.substring(0,10);
        }
        if(req.body.searchInfo.confTime != '' && req.body.searchInfo.confTime != null){
            searchInfo.confTime = req.body.searchInfo.confTime.substring(0,10);
        }
        if(req.body.searchInfo.deadLine != '' && req.body.searchInfo.deadLine!=null){
            searchInfo.deadLine = req.body.searchInfo.deadLine.substring(0,10);
        }
        if(req.body.searchInfo.subject != '' && req.body.searchInfo.subject != null){
            searchInfo.subject = req.body.searchInfo.subject;
        }
        if(req.body.searchInfo.location != '' && req.body.searchInfo.location != null){
            searchInfo.location = req.body.searchInfo.location;
        }
    }catch(err){
        console.log(err)
    }
    console.log(searchInfo);
    var content = JSON.stringify(searchInfo);
    console.log(content)
    fs.writeFileSync(des_file, content, 'utf8');
    /*
        在这里运行search 程序!!!
     */

    try {
        process.execSync('./search.sh');
    } catch (ex) {
        console.log(ex);
    }

    // 向前端发送搜索到的数据

    var raw_file = __dirname + "/" + '..' + "/" + 'Json' +"/" + 'searchResult.json';

    console.log(raw_file);
    try{
        var result=JSON.parse(fs.readFileSync(raw_file));
    }catch(err){
        console.log(err)
    }
    console.log(result);
    res.send(result);
    res.end('{"success":"true"}');

});

module.exports = router;