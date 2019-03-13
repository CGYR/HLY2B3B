module.exports =
    {
        mysql: {
            host: '127.0.0.1',
            user: 'root',
            password: 'hanfeng',
            database:'classweb', // 前面建的user表位于这个数据库中
            port: 3306
        }
    };
/*
var mysql=require("mysql");
var pool = mysql.createPool({
    host: 'localhost',
    user: 'root',
    password: 'hanfeng',
    database: 'classweb',
    port: 3306
});

var methodType = {
    // 项目所需
    login: select * from user where name= ? and password= ? ,
    //   type ---> 不放在服务器上面
    //  放入到服务器
    //  请求---> 根据传入进来的请求 数据库操作
    //  req.query    req.body
};
var query=function(sql,options,callback){
    pool.getConnection(function(err,conn){
        if(err){
            callback(err,null,null);
        }else{
            conn.query(sql,options,function(err,results,fields){
                //释放连接
                conn.release();
                //事件驱动回调
                callback(err,results,fields);
            });
        }
    });
};

var  sql = 'SELECT * FROM websites';
//查
connection.query(sql,function (err, result) {
    if(err){
        console.log('[SELECT ERROR] - ',err.message);
        return;
    }

    console.log('--------------------------SELECT----------------------------');
    console.log(result);
    console.log('------------------------------------------------------------\n\n');
});
module.exports = function(req,res,collections,selector,callback){
    pool.getConnection(function(err,conn){
        if(err){
            callback(null);
        }else{
            conn.query(methodType[req.route.path.substr(1)],selector,function(err,results,fields){
                //释放连接
                conn.release();
                //事件驱动回调
                callback(err,results,fields);
            });
        }
    });
    MongoClient.connect(Urls, function(err, db) {
        assert.equal(null, err);
        console.log("Connected correctly to server");
        // 根据 请求的地址来确定是什么操作  （为了安全，避免前端直接通过请求url操作数据库）
        methodType[req.route.path.substr(1)](db,collections,selector,fn);
        db.close();
    });
};
module.exports=query;
*/