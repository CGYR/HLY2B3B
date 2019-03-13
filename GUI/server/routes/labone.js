
var express = require('express');
var router = express.Router();
var formidable = require('formidable');
var fs = require("fs");
var process = require('child_process');

var path = require("path");

let sd = require('silly-datetime');

router.post('/labone_executeWorldlist', function(req, res, next) {
    console.log("labone_executeWorldlist 后端开始执行!");
    console.log(req.body);

    console.log(__dirname);
    wordinput = req.body.wordinfo.wordinput;
    // 后期可能需要修改路径
    des_file = __dirname+ "/../absolute_path_of_word_list";
    fs.writeFileSync(des_file, wordinput, 'utf8');
    console.log("成功写入文件")

    // 执行程序部分
    /*
    try {
        process.execSync('./search.sh');
    } catch (ex) {
        console.log(ex);
    }*/
    try{
        process.execSync('./yx -w');
    }catch(ex){
        console.log("fuck")
        console.log(ex)
    }
    // 向前端发送搜索到的数据


    // 读取执行后的程序
    // 后期可能需要修改路径
    des_file = __dirname + "/../solution.txt";
    /*
    try{
        var result=JSON.parse(fs.readFileSync(raw_file));
    }catch(err){
        console.log(err)
    }*/
    var result = fs.readFileSync(des_file).toString();

    console.log(result);
    res.send(result);
    res.end('{"success":"true"}');
    console.log("成功发送!");
});

module.exports = router;