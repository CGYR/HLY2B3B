
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

    // 这是测试demo
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

    var result = fs.readFileSync(des_file).toString();

    console.log(result);
    res.send(result);
    res.end('{"success":"true"}');
    console.log("成功发送!");
});

router.post("/file_upload",function(req,res,next){
    console.log(__dirname);
    //创建上传表单
    var form = new formidable.IncomingForm();
    //设置编码格式
    form.encoding = 'utf-8';
    //设置上传目录
    var uploadDir = __dirname+"/../";
    //保留后缀
    form.keepExtensions = true;
    //文件大小
    form.maxFieldsSize = 20 * 1024 * 1024;

    form.parse(req,function(err,fields,files){
        console.log("2");
        console.log(files);

        let filesFile = files.file;
        if (err) {
            return res.json({
                status: 500,
                msg: "内部服务器错误",
                result:''
            })
        }
        // 限制文件大小 单位默认字节 这里限制大小为20m
        if (filesFile.size > form.maxFieldsSize) {
            fs.unlink(filesFile.path);
            return res.json({
                status: '1',
                msg: "文件大小不能超过20M",
                result:''
            })
        }
        //后缀名
        // var extName = 'csv';
        /*
        switch (filesFile.type) {
            case 'image/jpg':
                extName = 'jpg';
                break;
            case 'image/jpeg':
                extName = 'jpg';
                break;
            case 'image/png':
                extName = 'png';
                break;
            case 'image/x-png':
                extName = 'png';
                break;
        }
        if (extName.length == 0) {
            return res.json({
                status: '1',
                msg: "只支持png和jpg格式图片",
                result:''
            })
        }*/
        var avatarName = "solution.txt";
        // 新图片路径
        var newPath = uploadDir + avatarName;
        fs.readFile(filesFile.path, function (err, data) {
            if (err) {
                console.log(err);
                return res.json({
                    "code": 401,
                    "message": "图片上传失败"
                })
            }
            console.log('File read!');
            // Write the file
            fs.writeFile(newPath, data, function (err) {
                if (err) throw err;
                res.write('File uploaded and moved!');
                res.end();
                console.log('File written!');
            });

            // Delete the file
            fs.unlink(filesFile.path, function (err) {
                if (err) throw err;
                console.log('File deleted!');
            });
        });
    })
});

module.exports = router;