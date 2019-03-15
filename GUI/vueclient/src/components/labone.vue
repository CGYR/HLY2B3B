<template>
  <div>
    <div style="height:2px;">
    </div>
      <!-- 内容部分 -->
      <el-card class="box-card" >
        <!-- 文件上传和内容输入  -->
        <el-row>
          <el-col :span="24">
            <el-switch
              v-model="upload_or_enter_set"
              active-color="#13ce66"
              inactive-color="#ff4949">
            </el-switch>&nbsp;&nbsp;切换输入方式
          </el-col>
        </el-row>
        <div style="height:8px;"></div>
        <div>
        <el-row>
          <!-- 输入 -->

          <el-col :span="11">
            <div v-if="upload_or_enter_set">
            <el-input
              type="textarea"
              :rows="2"
              :autosize="{ minRows: 12, maxRows: 12}"
              placeholder="请输入内容"
              v-model="wordinput"
              >
            </el-input>
            </div>
            <div v-if="!upload_or_enter_set" align="center">
              <!-- 部署到服务器上时，action可能需要修改 -->
              <el-upload
                class="upload-demo"
                drag
                action="http://localhost:3000/labone/file_upload"
                methods="post"
                :limit="1"
                multiple>
                <i class="el-icon-upload"></i>
                <div class="el-upload__text">将文件拖到此处，或<em>点击上传</em></div>
                <div class="el-upload__tip" slot="tip">请不要上传太大的文件,一次只允许上传一个文件</div>
              </el-upload>
            </div>
          </el-col>

          <!-- 输出 -->
          <el-col :span="11" :offset="1">
            <el-input
              type="textarea"
              :autosize="{ minRows: 12, maxRows: 12}"
              placeholder="输出结果"
              v-model="wordoutput"
              >
            </el-input>
          </el-col>
        </el-row>
        </div>
      </el-card>
      <el-card>
        <el-row>
          选择输入参数
        </el-row>
        <el-row>
          <el-col :span="4">
            -w:
            <el-switch
              v-model="w_set"
              active-color="#13ce66"
              inactive-color="#ff4949"
              :change="sayHellotest"
              >
            </el-switch>
          </el-col>
          <el-col :span="4">
            -c:
            <el-switch
              v-model="c_set"
              active-color="#13ce66"
              inactive-color="#ff4949">
            </el-switch>
          </el-col>
          <el-col :span="2">
            -h:
            <el-switch
              v-model="h_set"
              active-color="#13ce66"
              inactive-color="#ff4949">
            </el-switch>
          </el-col>
          <el-col :span="2">
            <el-input
              v-model="h_input"
              placeholder="-h"
              size="mini"
            >
            </el-input>
          </el-col>
          <el-col :span="2" :offset="1">
            -t:
            <el-switch
              v-model="t_set"
              active-color="#13ce66"
              inactive-color="#ff4949">
            </el-switch>
          </el-col>
          <el-col :span="2">
            <el-input
              v-model="t_input"
              placeholder="-t"
              size="mini"
            >
            </el-input>
          </el-col>
          <el-col :span="2" :offset="1">
            -n:
            <el-switch
              v-model="n_set"
              active-color="#13ce66"
              inactive-color="#ff4949">
            </el-switch>
          </el-col>
          <el-col :span="2">
            <el-input
              v-model="n_input"
              placeholder="-n"
              size="mini"
            >
            </el-input>
          </el-col>
        </el-row>
        <el-row>

        </el-row>
      </el-card>
      <!-- 显示生成的指令 -->
      <el-card>
        <el-row>
          生成的指令为:
        </el-row>
        <div style="height:4px"></div>
        <el-row>
        Worldlist.exe <span v-if="w_set">-w</span> <span v-if="c_set">-c</span>
        <span v-if="h_set">-h {{h_input}}</span>
        <span v-if="t_set">-t {{t_input}}</span>
        <span v-if="n_set">-n {{n_input}}</span>
        absolute_path_of_word_list
        </el-row>
      </el-card>
      <!-- 确认部分 -->
      <el-card>
        <div align="center">
        <el-button type="success" round @click="executeWordlist">点击执行Worldlist.exe程序</el-button>
        </div>
      </el-card>
  </div>
</template>

<script>
    export default {
      name: "labone",
      data() {
        return {
          upload_or_enter_set: true,
          wordinput: '',
          w_set: false,
          c_set: false,
          h_set: false,
          t_set: false,
          n_set: false,
          h_input: '',
          t_input: '',
          n_input: '',
          wordoutput: '',
        }
      },
      watch:{
        w_set: function(){
          if(this.c_set || this.n_set){
            this.w_set = false;
            this.showError("-w -c -n只能设置其中一个")
          }
        },
        c_set: function(){
          if(this.w_set || this.n_set){
            this.c_set = false;
            this.showError("-w -c -n只能设置其中一个")
          }
        },
        n_set: function(){
          if(this.w_set || this.c_set){
            this.n_set = false;
            this.showError("-w -c -n只能设置其中一个")
          }
        }
      },
      methods: {
        showError(words){
          this.$message({
            message: words,
            type: 'warning',
            showClose: true,
            duration:2000,
          })
        },
        executeWordlist(){
          // 防止
          if(!this.c_set && !this.w_set && !this.n_set){
            // 报错 至少需要设置一个
            this.showError("-w -c -n至少设置一个")
            return;
          }else if( this.h_set && this.h_input == ""){
            // 报错
            this.showError("-h 参数没有设置输入的字母")
            return;
          }else if( this.t_set && this.t_input == ""){
            // 报错
            this.showError("-t 参数没有设置输入的字母")
            return;
          }else if( this.n_set && this.n_input == ""){
            // 报错
            this.showError("-n 参数没有设置输入的数字")
            return;
          }
          console.log("bengin executeWordlist")
          var _this = this;
          this.$reqs.post("/labone/labone_executeWorldlist",{
            wordinfo:{
              upload_or_enter_set:this.upload_or_enter_set,
              w_set:this.w_set,
              c_set:this.c_set,
              h_set:this.h_set,
              t_set:this.t_set,
              n_set:this.n_set,
              h_input:this.h_input,
              t_input:this.t_input,
              n_input:this.n_input,
              wordinput:this.wordinput,
            }
          }).then(function(result){
            if(result.data.err){
              alert(result.data.err);
            }else{
              console.log("发送执行信息成功!")
              // console.log(result.data.mainJson);
              console.log(result.data);
              _this.wordoutput = result.data;
            }
          }).catch(function (error) {
            console.log("发送执行信息失败")
          });
        },
        sayHellotest(){
          console.log("hellow");
        }
      },
    }
</script>

<style scoped>

</style>
