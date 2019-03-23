
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

    wordinput = req.body.wordinfo.wordinput;
    // 后期可能需要修改路径
    des_file = __dirname+ "/../absolute_path_of_word_list";
    // 执行程序部分
    var parameter = req.body.wordinfo;
    // 首先判断何种上传方式
    if(parameter.upload_or_enter_set){
        // 输入上传
        fs.writeFileSync(des_file, wordinput, 'utf8');
        console.log("成功写入文件")
    }
    // 否则说明是文件方式上传，此处无需处理
    try{
        if(parameter.w_set){
            console.log("!!!")
            if(parameter.h_set && parameter.t_set) {
                process.execSync('./y -w -h '+parameter.h_input+' -t '+ parameter.t_input +' absolute_path_of_word_list');
            }else if(parameter.h_set){
                process.execSync('./y -w -h '+parameter.h_input+' absolute_path_of_word_list');
            }else if(parameter.t_set){
                process.execSync('./y -w -t '+parameter.t_input+' absolute_path_of_word_list');
            }else{
                process.execSync('./y -w absolute_path_of_word_list');
            }
        }else if(parameter.c_set){
            if(parameter.h_set && parameter.t_set) {
                process.execSync('./y -c -h '+parameter.h_input+' -t '+ parameter.t_input +' absolute_path_of_word_list');
            }else if(parameter.h_set){
                process.execSync('./y -c -h '+parameter.h_input+' absolute_path_of_word_list');
            }else if(parameter.t_set){
                process.execSync('./y -c -t '+parameter.t_input+' absolute_path_of_word_list');
            }else{
                process.execSync('./y -c absolute_path_of_word_list');
            }
        }else if(parameter.n_set){
            if(parameter.h_set && parameter.t_set) {
                process.execSync('./y -n '+parameter.n_input+' -h '+parameter.h_input+' -t '+ parameter.t_input +' absolute_path_of_word_list');
            }else if(parameter.h_set){
                process.execSync('./y -n '+parameter.n_input+' -h '+parameter.h_input+' absolute_path_of_word_list');
            }else if(parameter.t_set){
                process.execSync('./y -n '+parameter.n_input+' -t '+parameter.t_input+' absolute_path_of_word_list');
            }else{
                process.execSync('./y -n '+parameter.n_input+' absolute_path_of_word_list');
            }
        }

    }catch(ex){
        // 这里还需要增加一个执行错误报错
        console.log("fuck")
    }
    // 向前端发送搜索到的数据


    // 读取执行后的程序
    // 后期可能需要修改路径
    des_file = __dirname + "/../solution.txt";

    var result = fs.readFileSync(des_file).toString();
    if(result.length>10000){
        result = result.substring(0,10000)+"......\n(为了快速渲染，后面结果省略，可直接导出文件查看)"
    }
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
        var avatarName = "absolute_path_of_word_list";
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

// 下载文件
router.get('/download',function(req, res, next){
    console.log("download begin!");
    console.log(__dirname);
    var fileName = req.query.name;
    console.log(fileName);
    var currFile = __dirname + '/../' + fileName;
    console.log(currFile);
    var fReadStream = fs.createReadStream(currFile);
    console.log(currFile);
    fs.exists(currFile,function(exist) {
        if(exist){
            res.set({
                "Content-type":"application/octet-stream",
                "Content-Disposition":"attachment;filename="+encodeURI(fileName)
            });
            fReadStream = fs.createReadStream(currFile);
            fReadStream.on("data",(chunk) => res.write(chunk,"binary"));
            fReadStream.on("end",function () {
                res.end();
            });
        }else{
            res.set("Content-type","text/html");
            res.send("file not exist!");
            res.end();
        }
    });
});
module.exports = router;