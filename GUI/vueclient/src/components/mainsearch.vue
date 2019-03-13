<template>
    <!-- 主页的搜索框 -->
  <!-- 对每个条目使用el-card划分 -->
  <div>
    <div style="height:2px;">
    </div>
    <el-row>
      <el-col :span="24">
        <!-- search部分 -->
        <el-card class="box-card" >
          <el-row :gutter="20">
            <el-col :span="4">
              <div class="block">
                <span class="demonstration"></span>
                <el-date-picker
                  v-model="sendTime"
                  type="date"
                  placeholder="Send Time">
                </el-date-picker>
              </div>
            </el-col>

            <el-col :span="4">
              <div class="block">
                <span class="demonstration"></span>
                <el-date-picker
                  v-model="conferenceTime"
                  align="right"
                  type="date"
                  placeholder="Conference Time">
                </el-date-picker>
              </div>
            </el-col>

            <el-col :span="4">
              <div class="block">
                <span class="demonstration"></span>
                <el-date-picker
                  v-model="deadLine"
                  align="right"
                  type="date"
                  placeholder="DeadLine">
                </el-date-picker>
              </div>
            </el-col>

            <el-col :span="4">
              <el-input
                placeholder="enter subject for search"
                prefix-icon="el-icon-search"
                v-model="searchData">
              </el-input>
            </el-col>

            <el-col :span="4">
              <el-input
                placeholder="Location"
                prefix-icon="el-icon-search"
                v-model="location">
              </el-input>
            </el-col>

            <el-col :span="4">
              <el-button round @click="searchGo">开始检索</el-button>
            </el-col>
          </el-row>
        </el-card>
      </el-col>
      <!-- search部分 -->
    </el-row>
    <div style="height:5px;">
    </div>
    <!-- tbodys部分 -->
    <el-row>
      <el-table
        :data="paginationShow"
        border
        style="width: 100%"
      >
        <el-table-column
          prop="startTime"
          label="Send"
          sortable
          width="180">
        </el-table-column>

        <el-table-column
          prop="messageType"
          label="Message Type"
          width="180">
          <template slot-scope="scope">
            <span v-for="tag in scope.row.messageType" style="margin-right:4px;">
             <el-tag>
                {{tag.message}}
              </el-tag>
            </span>
          </template>
        </el-table-column>

        <el-table-column
          prop="from"
          label="From">
        </el-table-column>
        <el-table-column
          prop="subject"
          label="Subject">
          <template slot-scope="scope">
            <a :href="scope.row.subjectHref">{{scope.row.subject}}</a>
          </template>
        </el-table-column>

        <el-table-column
          prop="deadline"
          sortable
          label="Deadline">
        </el-table-column>

        <el-table-column
          prop="confTime"
          label="Conference Time"
          width="180">
        </el-table-column>

        <el-table-column
          prop="location"
          label="Location"
          width="180">
        </el-table-column>


      </el-table>
    </el-row>
    <!-- tbodys部分 -->
    <!-- 分页部分 -->
    <div style="height: 5px;">
    </div>
    <el-row>
      <el-col :span="24">
        <el-card class="box-card" >
          <div align="center">
            <el-pagination
              background
              layout="prev, pager, next"
              :current-page.sync="current_page"
              :total="shuldShowTBodys.length"
              @current-change="currentPage">
            </el-pagination>
          </div>
        </el-card>
      </el-col>
    </el-row>
    <!-- 分页部分 -->
  </div>
</template>

<script>
    export default {
      mounted(){
        this.initTBodys(); // 完成tbodys初始化

      },
      data() {
        return {
          tbodys:[ // 存放每一个条目 也就是总的tbodys

          ],
          shuldShowTBodys:[ // 存放应该展示的tdodys，也就是搜索得到的tbodys

          ],
          paginationShow:[  // 当前分页显示的条目

          ],
          sendTime:'',
          conferenceTime:'',
          options: [{
            value: 'conf',
            label: 'conf'
          }, {
            value: 'ann',
            label: 'ann'
          }, {
            value: 'job',
            label: 'job'
          }, {
            value: 'grants',
            label: 'grants'
          }, {
            value: 'journal',
            label: 'journal'
          },{
            value: 'book',
            label: 'book'
          },{
            value: 'CFC',
            label: 'CFC'
          },{
            value: 'CFP',
            label: 'CFP'
          },{
            value: 'news',
            label: 'news'
          },],
          deadLine:'',
          current_page:1,
          searchData:'',
          location:'',
        };
      },
      methods: {
        initTBodys(){ // 初始化tbodys 也就是展示例所有tbodys
          var _this = this;
          this.$reqs.post("/search/initTBodys",{
            // 什么也不用发送 就是告诉后端一个信息
          }).then(function(result){
            if(result.data.err){
              alert(result.data.err);
            }else{
              console.log("初始化tbodys获取成功")
              console.log(result.data.tbodys)
              _this.tbodys = result.data.tbodys;
              for(var i = 0;i<_this.tbodys.length;++i){
                _this.shuldShowTBodys.push(_this.tbodys[i]);
              }
              // 初始化
              _this.current_page = 1;
              for(var i=0;i<10;++i){
                _this.paginationShow.push(_this.shuldShowTBodys[i]);
              }
              console.log("*****")
              console.log(_this.paginationShow)
            }
          }).catch(function (error) {
            console.log("初始化tbodys获取失败")
          });
        },
        /*
        *   分页
        * */
        currentPage(){
          console.log("go "+this.current_page+" Page");
          this.paginationShow.length = 0;
          for(var i = (this.current_page-1)*10;i<(this.current_page)*10 && i<this.shuldShowTBodys.length;++i){
            this.paginationShow.push(this.shuldShowTBodys[i]);
          }
          console.log(this.paginationShow)
        },
        /**
         *  开始检索,以json格式向后端发送一个检索信息文件
         */
        searchGo(){
          console.log("go search!")
          console.log(this.sendTime)
          var _this = this;
          this.$reqs.post("/search/searchInfo",{
            searchInfo:{
              sendTime:this.sendTime,
              confTime:this.conferenceTime,
              deadLine:this.deadLine,
              subject:this.searchData,
              location:this.location,
            }
          }).then(function(result){
            if(result.data.err){
              alert(result.data.err);
            }else{
              console.log("发送检索信息成功")
              console.log(result.data.mainJson);
              _this.shuldShowTBodys.length = 0;
              console.log(_this.tbodys.length)
              if(result.data.mainJson.length == 0){
                // 处理没有搜到的情况
                while(_this.shuldShowTBodys.length !=0){
                  _this.shuldShowTBodys.pop();
                  console.log("pop!");
                }
                while(_this.paginationShow.length != 0){
                  _this.paginationShow.pop();
                  console.log("pop too!")
                }
              }else{
                for(var i=0;i<_this.tbodys.length;++i){
                  if(result.data.mainJson.indexOf(_this.tbodys[i].id)!=-1){
                    console.log("find"+_this.tbodys[i].id)
                    _this.shuldShowTBodys.push(_this.tbodys[i]);
                  }
                }
                console.log(_this.shuldShowTBodys);
                _this.current_page = 1;
                _this.paginationShow.length = 0;
                for(var i=0;i<10 && i<_this.shuldShowTBodys.length;++i){
                  _this.paginationShow.push(_this.shuldShowTBodys[i]);
                }
              }





              console.log(_this.shuldShowTBodys);
            }
          }).catch(function (error) {
            console.log("发送检索信息失败失败")
          });
        }
      }
    }
</script>

<style scoped>

</style>
